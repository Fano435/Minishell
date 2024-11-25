#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
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
// # define FILE 8

# define ERR_MALLOC "malloc error\n"
# define ERR_FORK "fork error\n"

extern pid_t		g_signal;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	bool			skip_cmd;
	int				infile;
	int				outfile;
	char			**cmd_args;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	t_list			*env;
	t_token			*tokens;
	t_cmd			*cmds;
	int				exit_code;
	int				pipe[2];
}					t_data;

void				print_error(char *str);
void				signals(void);
char				*header_prompt(void);
void				init_data(int ac, char **av, char **env, t_data *data);

// builtins
void				ft_echo(char **args);
void				ft_cd(t_data *data, char **args);
void				ft_pwd(t_data *data);
void				ft_export(t_data *data, char **args);
void				ft_unset(t_data *data, char **args);
void				ft_env(t_data *data);
void				ft_exit(t_data *data, char **args);

// builtins_utils
int					var_pos(t_list *env, char *var);
char				*get_var_value(char *var);

// list_utils
void				print_list(t_list *list);
void				free_list(t_list **list);
char				*find_var(t_list **lst, char *str);
t_list				*sort_list(t_list *list);

// token
void				create_token_list(t_data *data, char *line);

// token_utils
void				assign_words_type(t_token *token);
void				copy_token(char *str, char *word, int len);
void				print_tokens(t_token *list);
void				append_token(t_token **tokken_list, char *str, int type);

// cmd
void				create_cmd_list(t_data *data, t_token *token);

// cmd_utils
void				append_cmd(t_cmd **cmd_list, char **args, int infile,
						int outfile);

// cmd_args
int					count_args(t_token **token);
char				**get_cmd_args(t_token **token);

#endif