#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

# define INPUT 1
# define HEREDOC 2
# define TRUNC 3
# define APPEND 4
# define PIPE 5
# define CMD 6
# define ARG 7

# define ERR_MALLOC "malloc error\n"
# define ERR_PIPE "pipe error\n"
# define ERR_FORK "fork error\n"

# define PATH_MAX 255

extern pid_t		g_signal;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	t_list			*env;
	t_token			*token;
	int				exit_code;
	int				pipe[2];
}					t_data;

void				print_error(char *str);
void				signals(void);
char				*header_prompt(void);
void				init_data(int ac, char **av, char **env, t_data *data);

// builtins
void				ft_echo(char **args);
void				ft_cd(t_data *data, char *path);
void				ft_pwd(t_data *data);
void				ft_export(t_data *data, char **args);

// list_utils
void				print_list(t_list *list);
void				free_list(t_list **list);
char				*find_var(t_list **lst, char *str);
t_list				*sort_list(t_list *list);

#endif