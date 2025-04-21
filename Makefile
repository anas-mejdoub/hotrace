NAME = hotrace

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = src/main.c src/helpers/ft_free.c src/utils/ft_realloc.c src/utils/ft_memcpy.c src/utils/ft_memchr.c src/utils/ft_strdup.c src/utils/ft_strlen.c src/utils/ft_strcmp.c src/utils/ft_calloc.c src/utils/ft_bzero.c \
		src/tool/get_line.c src/helpers/ft_hts.c src/helpers/hash.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c hotrace.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all