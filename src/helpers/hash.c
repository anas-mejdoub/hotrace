/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabenman <yabenman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:08:37 by amejdoub          #+#    #+#             */
/*   Updated: 2025/04/20 17:30:50 by yabenman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hotrace.h"

unsigned long	hash(char *key, size_t table_size)
{
	unsigned long	h;

	h = 0;
	while (*key)
	{
		h = (h * 31) + *key;
		++key;
	}
	return (h % table_size);
}

unsigned long	hash2(char *key)
{
	unsigned long	h;

	h = 0;
	while (*key)
	{
		h = (h * 17) + *key;
		++key;
	}
	return (h | 1);
}
