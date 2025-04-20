/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:30:11 by amejdoub          #+#    #+#             */
/*   Updated: 2025/04/20 16:34:24 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hotrace.h"

char	*ft_strdup(const char *str)
{
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = ft_strlen2(str);
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
