/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:30:10 by amejdoub          #+#    #+#             */
/*   Updated: 2025/04/20 17:12:24 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

#define GET_BUFFER_SIZE 8192
#define OUTPUT_BUFFER_SIZE 8192
#define INITIAL_TABLE_SIZE 1048576 // 2^20, a power of 2 for faster modulo
#define MAX_LOAD_FACTOR 0.7

# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "../get_next_line/get_next_line.h"

typedef struct s_entry {
    char *key;
    char *value;
    int occupied; // 0: empty, 1: occupied, 2: deleted
} t_entry;

typedef struct s_hash_table {
    size_t size;
    size_t count;
    t_entry *entries;
} t_hash_table;

typedef struct {
    char buffer[GET_BUFFER_SIZE];
    size_t pos;
    size_t size;
} InputBuffer;

char		*get_next_line(int fd);
char		*ft_strjoin(char *s1, char *s2);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
char		*ft_strdup(const char *str);
size_t		ft_strlen2(const char *s);
int			ft_strcmp(const char *str1, const char *str2);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t num_elements, size_t element_size);
char *get_line(int fd);
unsigned long hash(char *key, size_t table_size);
unsigned long hash2(char *key);
t_hash_table *ht_create(size_t size);
void ht_resize(t_hash_table *ht);
void ht_insert(t_hash_table *ht, char *key, char *value);
char *ht_search(t_hash_table *ht, char *key);
void ht_free(t_hash_table *ht);
#endif
