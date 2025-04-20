/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:08:37 by amejdoub          #+#    #+#             */
/*   Updated: 2025/04/20 17:09:33 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hotrace.h"

unsigned long hash(char *key, size_t table_size)
{
    unsigned long h = 0;
    for (; *key; ++key) {
        h = (h * 31) + *key;
    }
    return h % table_size;
}

unsigned long hash2(char *key)
{
    unsigned long h = 0;
    for (; *key; ++key) {
        h = (h * 17) + *key;
    }
    return h | 1;
}
