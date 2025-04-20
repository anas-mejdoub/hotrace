/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabenman <yabenman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:40:11 by yabenman          #+#    #+#             */
/*   Updated: 2025/04/20 17:41:08 by yabenman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hotrace.h"

void	ht_free(t_hash_table *ht)
{
	size_t	i;

	i = 0;
	while (i < ht->size)
	{
		if (ht->entries[i].occupied == 1)
		{
			free(ht->entries[i].key);
			free(ht->entries[i].value);
		}
		i++;
	}
	free(ht->entries);
	free(ht);
}
