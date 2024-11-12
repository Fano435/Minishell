NAME = Minishell
OBJS = $(SRCS:.c=.o)
SRCS = main.c signal.c

CFLAGS = -Wall -Wextra -Werror 
LIBFT_LIB = libft/libft.a

.PHONY: all clean fclean re

all: ${NAME}

${LIBFT_LIB}:
	make -C libft

${NAME}: ${OBJS} ${LIBFT_LIB}
	cc $(CFLAGS) -o $@ $^ -I./ -lreadline

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: 
	make fclean -C libft
	make clean
	rm -f $(NAME)


re: 
	make fclean 
	make all