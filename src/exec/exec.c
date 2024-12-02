/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:55:33 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/02 17:55:32 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_redirections(t_data *data, t_cmd *cmd, int input_fd, int pipe_fd)
{
	if (cmd->infile != NO_FD)
	{
		dup2(cmd->infile, STDIN_FILENO);
		if (cmd != data->cmds)
			close(cmd->infile);
	}
	else
		dup2(input_fd, STDIN_FILENO);
	if (cmd->outfile != NO_FD)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	else if (cmd->next)
		dup2(pipe_fd, STDOUT_FILENO);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
}

void	exec_parent(t_data *data, t_cmd *cmd, int input_fd)
{
	if (is_builtin(cmd->cmd_params[0]))
		builtin(data, cmd, input_fd, NO_FD);
	else if (fork() == 0)
	{
		cmd_redirections(data, cmd, input_fd, 1);
		exec(data, cmd);
		exit(EXIT_FAILURE);
	}
}

void	exec_child(t_data *data, t_cmd *cmd, int input_fd, int pipe_fd[2])
{
	if (is_builtin(cmd->cmd_params[0]))
		builtin(data, cmd, input_fd, pipe_fd[1]);
	else if (fork() == 0)
	{
		cmd_redirections(data, cmd, input_fd, pipe_fd[1]);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exec(data, cmd);
		exit(EXIT_FAILURE);
	}
}

void	exec_pipeline(t_data *data)
{
	int		pipe_fd[2];
	int		input_fd;
	t_cmd	*cmd;

	input_fd = 0;
	cmd = data->cmds;
	while (cmd)
	{
		if (!cmd->next)
		{
			exec_parent(data, cmd, input_fd);
			break ;
		}
		pipe(pipe_fd);
		exec_child(data, cmd, input_fd, pipe_fd);
		close(pipe_fd[1]);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		input_fd = pipe_fd[0];
		cmd = cmd->next;
	}
}
