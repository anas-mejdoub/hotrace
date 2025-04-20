/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:17:28 by yabenman          #+#    #+#             */
/*   Updated: 2025/04/20 18:16:23 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# define GET_BUFFER_SIZE 8192
# define OUTPUT_BUFFER_SIZE 8192
# define INITIAL_TABLE_SIZE 1048576
# define MAX_LOAD_FACTOR 0.7

# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_entry
{
	char	*key;
	char	*value;
	int		occupied;
}	t_entry;

typedef struct s_hash_table
{
	size_t	size;
	size_t	count;
	t_entry	*entries;
}	t_hash_table;

typedef struct s_input_buffer
{
	char	buffer[GET_BUFFER_SIZE];
	size_t	pos;
	size_t	size;
}	t_input_buffer;

void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
char			*ft_strdup(const char *str);
size_t			ft_strlen(const char *s);
int				ft_strcmp(const char *str1, const char *str2);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t num_elements, size_t element_size);
char			*get_line(int fd);
void			*ft_realloc(void *ptr, size_t size);
void			ht_free(t_hash_table *ht);
unsigned long	hash(char *key, size_t table_size);
unsigned long	hash2(char *key);
t_hash_table	*ht_create(size_t size);
void			ht_resize(t_hash_table *ht);
void			ht_insert(t_hash_table *ht, char *key, char *value);
char			*ht_search(t_hash_table *ht, char *key);
void			ht_free(t_hash_table *ht);
void			ht_resize_entries(t_hash_table *ht, t_entry *old_entries, \
				size_t old_size);

#endif
