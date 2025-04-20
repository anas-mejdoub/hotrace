/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:10:11 by amejdoub          #+#    #+#             */
/*   Updated: 2025/04/20 17:12:15 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hotrace.h"

t_hash_table *ht_create(size_t size)
{
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

void ht_resize(t_hash_table *ht)
{
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

void ht_insert(t_hash_table *ht, char *key, char *value)
{
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

char *ht_search(t_hash_table *ht, char *key)
{
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

void ht_free(t_hash_table *ht)
{
    for (size_t i = 0; i < ht->size; i++) {
        if (ht->entries[i].occupied == 1) {
            free(ht->entries[i].key);
            free(ht->entries[i].value);
        }
    }
    free(ht->entries);
    free(ht);
}
