/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabenman <yabenman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:08:29 by yabenman          #+#    #+#             */
/*   Updated: 2025/04/20 17:09:42 by yabenman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hotrace.h"

void *ft_realloc(void *ptr, size_t size) {
    void *new_ptr = malloc(size);
    if (!new_ptr) {
        free(ptr);
        return NULL;
    }
    
    if (ptr) {
        ft_memcpy(new_ptr, ptr, size);
        free(ptr);
    }

    return new_ptr;
}
