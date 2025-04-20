/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:30:10 by amejdoub          #+#    #+#             */
/*   Updated: 2025/04/20 11:09:36 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
#define HOTRACE_H
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../get_next_line/get_next_line.h"
typedef struct s_node {
    char        *key;
    char        *value;
    struct s_node *next;
} t_node;
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
typedef struct s_hash_table {
    t_node **buckets;  // Array of linked list pointers
    size_t  size;       // Total buckets (e.g., a prime number like 100003)
} t_hash_table;
#endif