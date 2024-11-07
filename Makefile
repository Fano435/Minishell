NAME = Minishell
OBJS = $(SRCS:.c=.o)
SRCS = main.c 

CFLAGS = -Wall -Wextra -Werror -lreadline

.PHONY: all clean fclean re

all: ${NAME}

${NAME}: ${OBJS} 
	cc $(CFLAGS) -o $@ $^ -I./

clean:
	rm -f $(OBJS)

fclean: 
	make clean
	rm -f $(NAME)


re: 
	make fclean 
	make all