/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:53:44 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/30 15:16:06 by jrasamim         ###   ########.fr       */
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

int	exec_builtin_cmd(t_data *data, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd_params[0], "echo") == 0)
		return (ft_echo(cmd->cmd_params));
	if (ft_strcmp(cmd->cmd_params[0], "cd") == 0)
		return (ft_cd(data, cmd->cmd_params));
	if (ft_strcmp(cmd->cmd_params[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->cmd_params[0], "export") == 0)
		return (ft_export(data, cmd->cmd_params));
	if (ft_strcmp(cmd->cmd_params[0], "unset") == 0)
		return (ft_unset(data, cmd->cmd_params));
	if (ft_strcmp(cmd->cmd_params[0], "env") == 0)
		return (ft_env(data));
	if (ft_strcmp(cmd->cmd_params[0], "exit") == 0)
		return (ft_exit(cmd->cmd_params, NULL));
	return (0);
}

void	no_fork_builtin(t_data *data, t_cmd *cmd)
{
	int		saved_stdin;
	int		saved_stdout;
	bool	m_exit;

	m_exit = true;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	cmd_redirections(data, cmd, STDIN_FILENO, STDOUT_FILENO);
	if (ft_strcmp(cmd->cmd_params[0], "exit") == 0)
	{
		data->exit_code = ft_exit(cmd->cmd_params, &m_exit);
		if (m_exit)
		{
			close(saved_stdin);
			close(saved_stdout);
			exit(data->exit_code);
		}
	}
	else
		data->exit_code = exec_builtin_cmd(data, cmd);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
