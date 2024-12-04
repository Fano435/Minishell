NAME = minishell
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDE	=	-I ./include -I ./libft
LIBFT_LIB = libft/libft.a

FILES = main init signal list_utils ft_echo ft_cd ft_pwd ft_export ft_env ft_unset \
		ft_exit token token_utils create_cmd cmd_utils cmd_fds exec parsing parsing_utils \
		utils builtins exec_parsing heredoc
		
SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

OBJF	=	.cache_exits

$(OBJF) :
	@mkdir -p $(OBJ_DIR)

vpath %.c $(SRC_DIR) $(SRC_DIR)builtins $(SRC_DIR)exec $(SRC_DIR)parsing $(SRC_DIR)tokens_cmds

.PHONY: all clean fclean re

all: ${NAME}

${NAME}: ${OBJS} $(LIBFT_LIB)
	cc $(CFLAGS) $(OBJS) $(LIBFT_LIB) -lreadline $(INCLUDE) -o $@

$(OBJ_DIR)%.o : %.c Makefile | $(OBJF)
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