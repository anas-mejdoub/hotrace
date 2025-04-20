/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:45:33 by amejdoub          #+#    #+#             */
/*   Updated: 2025/04/20 16:46:35 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hotrace.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	void	*res;

	res = malloc(num_elements * element_size);
	if (!res)
		return (NULL);
	ft_bzero(res, num_elements * element_size);
	return (res);
}
