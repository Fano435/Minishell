/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:05:06 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/25 18:46:38 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal;

char	*header_prompt(void)
{
	char	curr_dir[1024];
	char	*login;

	login = getenv("USER");
	ft_strlcat(login, "@~", ft_strlen(login) + 3);
	getcwd(curr_dir, sizeof(curr_dir));
	if (ft_strcmp(getenv("USER"), "root") == 0)
		ft_strlcat(curr_dir, "# ", sizeof(curr_dir));
	else
		ft_strlcat(curr_dir, "$ ", sizeof(curr_dir));
	ft_strlcat(login, curr_dir, sizeof(curr_dir));
	return (ft_strdup(login));
}

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp("echo", cmd, INT_MAX) || !ft_strncmp("cd", cmd, INT_MAX)
		|| !ft_strncmp("pwd", cmd, INT_MAX) || !ft_strncmp("export", cmd,
			INT_MAX) || !ft_strncmp("unset", cmd, INT_MAX) || !ft_strncmp("env",
			cmd, INT_MAX) || !ft_strncmp("exit", cmd, INT_MAX))
		return (true);
	return (false);
}

void	exec_builtin(t_data *data, char *cmd, char **args)
{
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(args);
	if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(data, args);
	if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd(data);
	if (ft_strcmp(cmd, "export") == 0)
		ft_export(data, args);
	if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(data, args);
	if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(data, args);
	if (ft_strcmp(cmd, "env") == 0)
		ft_env(data);
	if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(data, args);
}

int	main(int ac, char **av, char **env)
{
	char	*rl;
	t_data	data;

	init_data(ac, av, env, &data);
	while (1)
	{
		rl = readline("minishell > ");
		if (rl == NULL)
			break ;
		create_token_list(&data, rl);
		// print_tokens(data.tokens);
		create_cmd_list(&data, data.tokens);
		add_history(rl);
		// continue ;
		if (is_builtin(data.cmds->cmd_params[0]))
			exec_builtin(&data, data.cmds->cmd_params[0],
				&data.cmds->cmd_params[1]);
		else
		{
			exec_pipeline(&data);
			wait(NULL);
		}
		g_signal = 0;
	}
	rl_clear_history();
	return (0);
}
