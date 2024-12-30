/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:57:43 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/27 18:22:56 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ERR_FILE_OPEN -1
# define NO_FD -2

# define INPUT 1
# define HEREDOC 2
# define TRUNC 3
# define APPEND 4
# define PIPE 5
# define CMD 6
# define ARG 7

# define CMD_NOT_FOUND 127
# define CMD_NO_EXEC 126

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
	char			**cmd_params;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	t_list			*env;
	t_token			*tokens;
	t_cmd			*cmds;
	int				exit_code;

}					t_data;

int					ft_tablen(char **tab);

void				print_error(char *str);
void				signals(void);
void				cmd_sig(int code);
void				handle_sigint(int code);
void				init_data(int ac, char **av, char **env, t_data *data);
void				here_doc(char *lim, t_data *data);

// builtins
int					ft_echo(char **args);
int					ft_cd(t_data *data, char **args);
int					ft_pwd(void);
int					ft_export(t_data *data, char **args);
int					ft_unset(t_data *data, char **args);
int					ft_env(t_data *data);
int					ft_exit(char **params, bool *exit);
bool				is_builtin(char *cmd);
void				no_fork_builtin(t_data *data, t_cmd *cmd);

// free
void				free_tokens(t_token **token);
void				free_cmds(t_cmd **list);
void				free_env(t_list **list);

// builtins_utils
int					var_pos(t_list *env, char *var);
char				*get_var_value(char *var);
bool				valid_identifier(char *str);

// list_utils
void				print_list(t_list *list);
void				free_list(t_list **list);
char				*find_var(t_list **lst, char *str);
t_list				*sort_list(t_list *list);

// token
void				create_token_list(t_data *data, char *line);

// token_utils
void				assign_words_type(t_token **token);
void				copy_token(char *str, char *word, int len);
void				print_tokens(t_token *list);
void				append_token(t_token **tokken_list, char *str, int type);
int					is_operator(char *str);
int					check_syntax(t_token **token);

// cmd
void				create_cmd_list(t_data *data, t_token *token);

// cmd_utils
void				append_cmd(t_cmd **cmd_list, char **args, int infile,
						int outfile);
void				print_cmd_list(t_cmd *list);
t_cmd				*ft_cmdlast(t_cmd *lst);

// cmd_params
int					count_params(t_token **token);
char				**get_cmd_params(t_data *data, t_token **token);
void				get_outfile(t_data *data, t_token **tokken);
void				get_infile(t_data *data, t_token **token);

// exec
void				exec_pipeline(t_data *data);
void				exec(t_data *data, t_cmd *cmd);
void				cmd_redirections(t_data *data, t_cmd *cmd, int input_fd,
						int pipe_fd);
int					exec_builtin_cmd(t_data *data, t_cmd *cmd);

// utils.c
int					skip_to_quotes(char *str, int i, char c);
int					check_closed_quotes(char *str);
int					advance(char *str, int i, char c);
char				*handle_dollar(char *str, char *substr, int *i);
int					check_full_w_s(char *str);

// parsing_utils.c
char				*handle_exit_status(char *str, int *i, t_data *data);
char				*handle_var_env_no_quotes(char *str, char *str_no_quotes,
						int *i, t_data *data);
char				*handle_char_no_quotes(char *str, char *str_no_quotes,
						int *i);
char				*handle_var_env_db_quotes(char *str, char *str_db_quotes,
						int *i, t_data *data);
char				*handle_char_db_quotes(char *str, char *str_db_quotes,
						int *i);
int					norm_if_db_q(char *s, int i);

// parsing.c
char				*parse_sing_quotes(char *str, int i, t_data *data);
char				*parse_db_quotes(char *str, int i, t_data *data);
char				*parse_no_quotes(char *str, int i, t_data *data);
char				*update_str_parsed(char *(*parser)(char *, int, t_data *),
						char *str, char *str_parsed, int i, t_data *data);
char				*parse_rl(char *str, t_data *data);

#endif
