/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabenman <yabenman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:01:30 by yabenman          #+#    #+#             */
/*   Updated: 2025/04/20 17:09:05 by yabenman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../hotrace.h"

char *get_line(int fd) {
    static InputBuffer b = { .pos = 0, .size = 0 };
    char *line = NULL;
    size_t line_size = 0, capacity = 128;

    line = malloc(capacity);
    if (!line) return NULL;

    while (1) {
        if (b.pos >= b.size) {
            b.size = read(fd, b.buffer, GET_BUFFER_SIZE);
            b.pos = 0;
            if (b.size <= 0) {
                if (line_size > 0) {
                    line[line_size] = '\0';
                    return line;
                }
                free(line);
                return NULL;
            }
        }

        size_t remaining = b.size - b.pos;
        char *nl = ft_memchr(b.buffer + b.pos, '\n', remaining);
        size_t len = nl ? (size_t)(nl - (b.buffer + b.pos)) : remaining;

        if (line_size + len + 1 > capacity) {
            capacity = (line_size + len + 1) * 2;
            char *new_line = ft_realloc(line, capacity);
            if (!new_line) {
                free(line);
                return NULL;
            }
            line = new_line;
        }

        ft_memcpy(line + line_size, b.buffer + b.pos, len);
        line_size += len;
        b.pos += len + (nl ? 1 : 0);

        if (nl) {
            line[line_size] = '\0';
            return line;
        }
    }
}