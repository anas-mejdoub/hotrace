/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabenman <yabenman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:29:42 by amejdoub        #+#    #+#             */
/*   Updated: 2025/04/20 15:03:35 by yabenman       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hotrace.h"
#define GET_BUFFER_SIZE 8192
#define OUTPUT_BUFFER_SIZE 8192
#define INITIAL_TABLE_SIZE 1048576 // 2^20, a power of 2 for faster modulo
#define MAX_LOAD_FACTOR 0.7

typedef struct s_entry {
    char *key;
    char *value;
    int occupied; // 0: empty, 1: occupied, 2: deleted
} t_entry;

typedef struct s_hash_table {
    size_t size;
    size_t count;
    t_entry *entries;
} t_hash_table;

typedef struct {
    char buffer[GET_BUFFER_SIZE];
    size_t pos;
    size_t size;
} InputBuffer;

char *get_line(int fd) {
    static InputBuffer b = { .pos = 0, .size = 0 };
    char *line = NULL;
    size_t line_size = 0, capacity = 128;

    line = malloc(capacity);
    if (!line) return NULL;

    while (1) {
        if (b.pos >= b.size) {
            b.size = read(fd, b.buffer, GET_BUFFER_SIZE);
            b.pos = 0;
            if (b.size <= 0) {
                if (line_size > 0) {
                    line[line_size] = '\0';
                    return line;
                }
                free(line);
                return NULL;
            }
        }

        size_t remaining = b.size - b.pos;
        char *nl = ft_memchr(b.buffer + b.pos, '\n', remaining);
        size_t len = nl ? (size_t)(nl - (b.buffer + b.pos)) : remaining;

        if (line_size + len + 1 > capacity) {
            capacity = (line_size + len + 1) * 2;
            char *new_line = realloc(line, capacity);
            if (!new_line) {
                free(line);
                return NULL;
            }
            line = new_line;
        }

        ft_memcpy(line + line_size, b.buffer + b.pos, len);
        line_size += len;
        b.pos += len + (nl ? 1 : 0);

        if (nl) {
            line[line_size] = '\0';
            return line;
        }
    }
}

unsigned long hash(char *key, size_t table_size) {
    unsigned long h = 0;
    for (; *key; ++key) {
        h = (h * 31) + *key;
    }
    return h % table_size;
}

unsigned long hash2(char *key) {
    unsigned long h = 0;
    for (; *key; ++key) {
        h = (h * 17) + *key;
    }
    return h | 1; // Ensure odd number for better probing
}

t_hash_table *ht_create(size_t size) {
    t_hash_table *ht = malloc(sizeof(t_hash_table));
    if (!ht) return NULL;
    ht->size = size;
    ht->count = 0;
    ht->entries = ft_calloc(size, sizeof(t_entry));
    if (!ht->entries) {
        free(ht);
        return NULL;
    }
    return ht;
}

// Function prototype to resolve implicit declaration
void ht_insert(t_hash_table *ht, char *key, char *value);

void ht_resize(t_hash_table *ht) {
    size_t new_size = ht->size * 2;
    t_entry *old_entries = ht->entries;
    size_t old_size = ht->size;

    ht->entries = ft_calloc(new_size, sizeof(t_entry));
    if (!ht->entries) {
        ht->entries = old_entries;
        return;
    }
    ht->size = new_size;
    ht->count = 0;

    for (size_t i = 0; i < old_size; i++) {
        if (old_entries[i].occupied == 1) {
            ht_insert(ht, old_entries[i].key, old_entries[i].value);
            free(old_entries[i].key);
            free(old_entries[i].value);
        }
    }
    free(old_entries);
}

void ht_insert(t_hash_table *ht, char *key, char *value) {
    if ((double)(ht->count + 1) / ht->size > MAX_LOAD_FACTOR) {
        ht_resize(ht);
    }

    unsigned long h1 = hash(key, ht->size);
    unsigned long h2 = hash2(key);
    size_t index = h1;

    while (ht->entries[index].occupied == 1) {
        if (ft_strcmp(ht->entries[index].key, key) == 0) {
            free(ht->entries[index].value);
            ht->entries[index].value = ft_strdup(value);
            return;
        }
        index = (index + h2) % ht->size;
    }

    if (ht->entries[index].occupied == 0) {
        ht->count++;
    }
    ht->entries[index].key = ft_strdup(key);
    ht->entries[index].value = ft_strdup(value);
    ht->entries[index].occupied = 1;
}

char *ht_search(t_hash_table *ht, char *key) {
    unsigned long h1 = hash(key, ht->size);
    unsigned long h2 = hash2(key);
    size_t index = h1;

    while (ht->entries[index].occupied != 0) {
        if (ht->entries[index].occupied == 1 && ft_strcmp(ht->entries[index].key, key) == 0) {
            return ht->entries[index].value;
        }
        index = (index + h2) % ht->size;
    }
    return NULL;
}

void ht_free(t_hash_table *ht) {
    for (size_t i = 0; i < ht->size; i++) {
        if (ht->entries[i].occupied == 1) {
            free(ht->entries[i].key);
            free(ht->entries[i].value);
        }
    }
    free(ht->entries);
    free(ht);
}

int main(void) {
    t_hash_table *ht = ht_create(INITIAL_TABLE_SIZE);
    if (!ht) return 1;

    char *key, *value, *result;

    // Insertion Phase
    while ((key = get_line(0))) {
        if (!*key) {
            free(key);
            break;
        }
        value = get_line(0);
        if (!value) {
            free(key);
            break;
        }
        if (*key && *value) {
            ht_insert(ht, key, value);
        }
        free(key);
        free(value);
    }

    // Search Phase
    while ((key = get_line(0))) {
        if (!*key) {
            free(key);
            continue;
        }
        result = ht_search(ht, key);
        if (result) {
            write(1, result, ft_strlen(result));
            write(1, "\n", 1);
        } else {
            write(1, key, ft_strlen(key));
            write(1, ": not found\n", 12);
        }
        free(key);
    }
    ht_free(ht);
    return 0;
}