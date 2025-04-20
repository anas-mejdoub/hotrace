/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabenman <yabenman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:49:47 by yabenman          #+#    #+#             */
/*   Updated: 2025/04/20 18:10:22 by yabenman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hotrace.h"

typedef struct s_line_ctx
{
	char	*line;
	size_t	line_size;
	size_t	capacity;
}	t_line_ctx;

static int	read_to_buffer(t_input_buffer *b, int fd)
{
	b->size = read(fd, b->buffer, GET_BUFFER_SIZE);
	b->pos = 0;
	if (b->size <= 0)
		return (0);
	return (1);
}

static char	*expand_line(t_line_ctx *ctx, size_t needed)
{
	char	*new_line;

	ctx->capacity = needed * 2;
	new_line = ft_realloc(ctx->line, ctx->capacity);
	if (!new_line)
		return (NULL);
	ctx->line = new_line;
	return (ctx->line);
}

static char	*process_line_chunk(t_input_buffer *b, t_line_ctx *ctx)
{
	size_t	remaining;
	size_t	len;
	char	*nl;

	remaining = b->size - b->pos;
	nl = ft_memchr(b->buffer + b->pos, '\n', remaining);
	if (nl)
		len = (size_t)(nl - (b->buffer + b->pos));
	else
		len = remaining;
	if (ctx->line_size + len + 1 > ctx->capacity)
		if (!expand_line(ctx, ctx->line_size + len + 1))
			return (NULL);
	ft_memcpy(ctx->line + ctx->line_size, b->buffer + b->pos, len);
	ctx->line_size += len;
	if (nl)
		b->pos += len + 1;
	else
		b->pos += len;
	if (nl)
	{
		ctx->line[ctx->line_size] = '\0';
		return (ctx->line);
	}
	return (NULL);
}

static char	*read_and_process(t_input_buffer *b, t_line_ctx *ctx, int fd)
{
	char	*result;

	if (b->pos >= b->size && !read_to_buffer(b, fd))
	{
		if (ctx->line_size > 0)
		{
			ctx->line[ctx->line_size] = '\0';
			return (ctx->line);
		}
		free(ctx->line);
		return (NULL);
	}
	result = process_line_chunk(b, ctx);
	if (result)
		return (result);
	return (NULL);
}

char	*get_line(int fd)
{
	static t_input_buffer	b = {.pos = 0, .size = 0};
	t_line_ctx				ctx;
	char					*result;

	ctx.capacity = 128;
	ctx.line_size = 0;
	ctx.line = malloc(ctx.capacity);
	if (!ctx.line)
		return (NULL);
	while (1)
	{
		result = read_and_process(&b, &ctx, fd);
		if (result)
			return (result);
	}
}
