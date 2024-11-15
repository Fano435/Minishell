NAME = minishell
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDE	=	-I ./include -I ./libft
LIBFT_LIB = libft/libft.a

FILES = main init signal list_utils ft_echo ft_cd ft_pwd ft_export

SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

OBJF	=	.cache_exits

$(OBJF) :
	@mkdir -p $(OBJ_DIR)

.PHONY: all clean fclean re

all: ${NAME}

${NAME}: ${OBJS} $(LIBFT_LIB)
	cc $(CFLAGS) $(OBJS) $(LIBFT_LIB) -lreadline $(INCLUDE) -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJF)
	cc $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT_LIB):
	make -C libft

clean:
	make clean -C libft
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJF)

fclean: 
	make fclean -C libft
	make clean
	rm -f $(NAME)


re: 
	make fclean 
	make all