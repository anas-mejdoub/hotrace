/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabenman <yabenman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:30:11 by amejdoub          #+#    #+#             */
/*   Updated: 2025/04/20 17:23:21 by yabenman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hotrace.h"

char	*ft_strdup(const char *str)
{
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = ft_strlen(str);
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
