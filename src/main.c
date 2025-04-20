/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:29:42 by amejdoub          #+#    #+#             */
/*   Updated: 2025/04/20 13:43:29 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>

#include "hotrace.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define GNL_BUFFER_SIZE 65536  // 64KB (optimal for modern SSDs)

typedef struct {
    char buffer[GNL_BUFFER_SIZE];
    size_t start;
    size_t end;
} Buffer;

char *get_line(int fd) {
    static Buffer b = { .start = 0, .end = 0 };
    
    while (1) {
        // Refill buffer when empty
        if (b.start >= b.end) {
            b.start = 0;
            b.end = read(fd, b.buffer, GNL_BUFFER_SIZE);
            if (b.end <= 0) return NULL;
        }

        // Scan for newline
        char *nl = memchr(b.buffer + b.start, '\n', b.end - b.start);
        if (nl) {
            size_t line_len = nl - (b.buffer + b.start) + 1;
            char *line = malloc(line_len + 1);
            memcpy(line, b.buffer + b.start, line_len);
            line[line_len] = '\0';
            b.start += line_len;
            return line;
        }

        // No newline - accumulate
        char *accumulated = malloc(b.end - b.start + 1);
        memcpy(accumulated, b.buffer + b.start, b.end - b.start);
        accumulated[b.end - b.start] = '\0';
        b.start = b.end;
    }
}




char output_buffer[65536];
size_t buffer_pos = 0;

void flush_buffer() {
    if (buffer_pos > 0) {
        write(1, output_buffer, buffer_pos);
        buffer_pos = 0;
    }
}

void buffered_write(const char *str) {
    size_t len = strlen(str);
    
    while (len > 0) {
        size_t space = 4096 - buffer_pos;
        size_t to_copy = len < space ? len : space;
        
        memcpy(output_buffer + buffer_pos, str, to_copy);
        buffer_pos += to_copy;
        str += to_copy;
        len -= to_copy;
        
        if (buffer_pos == 4096) {
            flush_buffer();
        }
    }
}

t_hash_table *ht_create(size_t size) {
    t_hash_table *ht = malloc(sizeof(t_hash_table));
    ht->size = size;
    ht->buckets = calloc(size, sizeof(t_node *));
    return ht;
}

// hash function 

unsigned long hash(char *key, size_t table_size) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;
    return hash % table_size;
}

void ht_insert(t_hash_table *ht, char *key, char *value) {
    unsigned long index = hash(key, ht->size);
    t_node *node = ht->buckets[index];
    while (node)
    {
        if (strcmp(node->key, key) == 0)
        {
            free(node->value);
            node->value = strdup(value);
            return;
        }
        node = node->next;
    }
    t_node *new_node = malloc(sizeof(t_node));
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
}

char *ht_search(t_hash_table *ht, char *key) {
    unsigned long index = hash(key, ht->size);
    t_node *node = ht->buckets[index];
    
    while (node) {
        if (strcmp(node->key, key) == 0)
            return node->value;
        node = node->next;
    }
    return NULL;
}

void ht_free(t_hash_table *ht) {
    for (size_t i = 0; i < ht->size; i++) {
        t_node *node = ht->buckets[i];
        while (node) {
            t_node *temp = node;
            node = node->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(ht->buckets);
    free(ht);
}
#include <stdio.h>

int main()
{
    char *result;
    // char *bulk_write;
    t_hash_table *ht = ht_create(100000003);

    unsigned long long i = 0;
    char *key = NULL;
    char *value = NULL;

    // First loop
    while (1)
    {
        key = get_line(0);
        if (key && key[strlen(key) - 1] == '\n')
            key[strlen(key) - 1] = '\0';
        if (!key || !key[0])
        {
            free(key);
            break;
        }

        value = get_line(0);
        if (value && value[strlen(value) - 1] == '\n')
            value[strlen(value) - 1] = '\0';
        printf("key %s | value %s\n", key, value);
        if (!value || !value[0])
        {
            printf("Error: value is empty\n");
            free(key);
            free(value);
            ht_free(ht);
            return 1;
        }
        ht_insert(ht, key, value);

        free(key);
        free(value);
        i++;
    }

    // Second loop
    while (1)
    {
        key = get_line(0);
        if (key && key[strlen(key) - 1] == '\n')
            key[strlen(key) - 1] = '\0';
        if (!key || !key[0])
        {
            free(key);
            break;
        }
        result = ht_search(ht, key);
        
        if (!result)
        {
            write(1, key, strlen(key));
            write(1, ":not found\n", 11);
        }
        else
        {
            // write(1, key, strlen(key));
            write(1, result, strlen(result));
            write(1, "\n", 1);
        }
        free(key);
    }
    flush_buffer();
    ht_free(ht);
}