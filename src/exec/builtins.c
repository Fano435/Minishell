/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:53:44 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/02 17:54:36 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exec_builtin_cmd(t_data *data, char **cmd_params)
{
	if (ft_strcmp(cmd_params[0], "echo") == 0)
		ft_echo(cmd_params);
	if (ft_strcmp(cmd_params[0], "cd") == 0)
		ft_cd(data, cmd_params);
	if (ft_strcmp(cmd_params[0], "pwd") == 0)
		ft_pwd(data);
	if (ft_strcmp(cmd_params[0], "export") == 0)
		ft_export(data, cmd_params);
	if (ft_strcmp(cmd_params[0], "unset") == 0)
		ft_unset(data, cmd_params);
	if (ft_strcmp(cmd_params[0], "env") == 0)
		ft_env(data);
	if (ft_strcmp(cmd_params[0], "exit") == 0)
		ft_exit(data, cmd_params);
}

void	builtin(t_data *data, t_cmd *cmd, int input_fd, int output_fd)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	cmd_redirections(data, cmd, input_fd, output_fd);
	exec_builtin_cmd(data, cmd->cmd_params);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
