NAME = hotrace

CC = cc

CFLAGS = -Wall -Wextra -Werror #./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c #-I ./get-next-line

SRCS = src/main.c ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

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