/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabenman <yabenman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:10:11 by amejdoub          #+#    #+#             */
/*   Updated: 2025/04/20 17:40:33 by yabenman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hotrace.h"

t_hash_table	*ht_create(size_t size)
{
	t_hash_table	*ht;

	ht = malloc(sizeof(t_hash_table));
	if (!ht)
		return (NULL);
	ht->size = size;
	ht->count = 0;
	ht->entries = ft_calloc(size, sizeof(t_entry));
	if (!ht->entries)
	{
		free(ht);
		return (NULL);
	}
	return (ht);
}

void	ht_resize(t_hash_table *ht)
{
	size_t		new_size;
	t_entry		*old_entries;
	size_t		old_size;

	new_size = ht->size * 2;
	old_entries = ht->entries;
	old_size = ht->size;
	ht->entries = ft_calloc(new_size, sizeof(t_entry));
	if (!ht->entries)
	{
		ht->entries = old_entries;
		return ;
	}
	ht->size = new_size;
	ht->count = 0;
	ht_resize_entries(ht, old_entries, old_size);
}

void	ht_resize_entries(t_hash_table *ht, t_entry *old_enrty, size_t old_size)
{
	size_t	i;

	i = 0;
	while (i < old_size)
	{
		if (old_enrty[i].occupied == 1)
		{
			ht_insert(ht, old_enrty[i].key, old_enrty[i].value);
			free(old_enrty[i].key);
			free(old_enrty[i].value);
		}
		i++;
	}
	free(old_enrty);
}

void	ht_insert(t_hash_table *ht, char *key, char *value)
{
	unsigned long	h1;
	unsigned long	h2;
	size_t			index;

	if ((double)(ht->count + 1) / ht->size > MAX_LOAD_FACTOR)
		ht_resize(ht);
	h1 = hash(key, ht->size);
	h2 = hash2(key);
	index = h1;
	while (ht->entries[index].occupied == 1)
	{
		if (ft_strcmp(ht->entries[index].key, key) == 0)
		{
			free(ht->entries[index].value);
			ht->entries[index].value = ft_strdup(value);
			return ;
		}
		index = (index + h2) % ht->size;
	}
	if (ht->entries[index].occupied == 0)
		ht->count++;
	ht->entries[index].key = ft_strdup(key);
	ht->entries[index].value = ft_strdup(value);
	ht->entries[index].occupied = 1;
}

char	*ht_search(t_hash_table *ht, char *key)
{
	unsigned long	h1;
	unsigned long	h2;
	size_t			index;

	h1 = hash(key, ht->size);
	h2 = hash2(key);
	index = h1;
	while (ht->entries[index].occupied != 0)
	{
		if (ht->entries[index].occupied == 1 
			&& ft_strcmp(ht->entries[index].key, key) == 0)
			return (ht->entries[index].value);
		index = (index + h2) % ht->size;
	}
	return (NULL);
}
