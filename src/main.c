/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:29:42 by amejdoub          #+#    #+#             */
/*   Updated: 2025/04/19 20:34:37 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
#include "hotrace.h"

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
void ll()
{
    system("leaks hotrace");
}
int main()
{
    atexit(ll);
    char *result;
    t_hash_table *ht = ht_create(100003);
    ht_insert(ht, "rag-1", "value1");
    ht_insert(ht, "rag-2", "value2");
    unsigned long long i = 0;
    char *key = NULL;
    char *value = NULL;

    // First loop
    while (1)
    {
        key = get_next_line(0);
        if (key && key[strlen(key) - 1] == '\n')
            key[strlen(key) - 1] = '\0';
        value = get_next_line(0);
        if (value && value[strlen(value) - 1] == '\n')
            value[strlen(value) - 1] = '\0';
        if (!key || !value || !key[0] || !value[0])
        {
            free(key);
            free(value);
            break;
        }
        ht_insert(ht, key, value);
        free(key);
        free(value);
        i++;
    }

    // Second loop
    while (1)
    {
        key = get_next_line(0);
        if (key && key[strlen(key) - 1] == '\n')
            key[strlen(key) - 1] = '\0';
        if (!key || !key[0])
        {
            free(key);
            break;
        }
        result = ht_search(ht, key);
        write(1, key, strlen(key)); 
        if (!result)
        {
            write(1, ":not found\n", 12);
        }
        else
        {
            write(1, ":", 1);
            write(1, result, strlen(result));
            write(1, "\n", 1);
        }
        free(key);
    }

    ht_free(ht);
}