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

#include "hotrace.h"

void	insertion_phase(char *key, char *value, t_hash_table *ht)
{
	while (1)
	{
		key = get_line(0);
		if (!key || !*key)
		{
			free(key);
			break ;
		}
		value = get_line(0);
		if (!value)
		{
			free(key);
			break ;
		}
		if (*key && *value)
		{
			ht_insert(ht, key, value);
		}
		free(key);
		free(value);
	}
}

void	search_phase(char *key, t_hash_table *ht)
{
	char	*result;

	while (1)
	{
		key = get_line(0);
		if (!key || !*key)
		{
			free(key);
			break ;
		}
		result = ht_search(ht, key);
		if (result)
		{
			write(1, result, ft_strlen(result));
			write(1, "\n", 1);
		}
		else
		{
			write(1, key, ft_strlen(key));
			write(1, ": not found\n", 12);
		}
		free(key);
	}
}

int	main(void)
{
	t_hash_table	*ht;
	char			*key;
	char			*value;

	value = NULL;
	key = NULL;
	ht = ht_create(INITIAL_TABLE_SIZE);
	if (!ht)
		return (1);
	insertion_phase(key, value, ht);
	search_phase(key, ht);
	ht_free(ht);
	return (0);
}
