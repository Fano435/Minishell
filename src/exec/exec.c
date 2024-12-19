/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:55:33 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/19 19:27:33 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_redirections(t_data *data, t_cmd *cmd, int input_fd, int fd_out)
{
	(void)data;
	if (cmd->infile >= 0)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	else
		dup2(input_fd, STDIN_FILENO);
	if (cmd->outfile >= 0)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	else if (cmd->next)
		dup2(fd_out, STDOUT_FILENO);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
}

void	exec_last(t_data *data, t_cmd *cmd, int input_fd)
{
	if (is_builtin(cmd->cmd_params[0]) && data->cmds == cmd)
	{
		cmd_redirections(data, cmd, input_fd, 1);
		if (ft_strcmp(cmd->cmd_params[0], "exit") == 0)
		{
			wait(NULL);
			if (input_fd != STDIN_FILENO)
				close(input_fd);
			printf("exit\n");
			exit(ft_exit(cmd->cmd_params));
		}
		builtin(data, cmd);
	}
	else if (fork() == 0)
	{
		cmd_redirections(data, cmd, input_fd, 1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (is_builtin(cmd->cmd_params[0]))
		{
			exit(exec_builtin_cmd(data, cmd));
		}
		exec(data, cmd);
		exit(EXIT_FAILURE);
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
}

void	exec_child(t_data *data, t_cmd *cmd, int input_fd, int pipe_fd[2])
{
	if (fork() == 0)
	{
		cmd_redirections(data, cmd, input_fd, pipe_fd[1]);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (is_builtin(cmd->cmd_params[0]))
			exit(exec_builtin_cmd(data, cmd));
		exec(data, cmd);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
}

void	wait_all(t_data *data)
{
	t_cmd	*cmd;
	int		i;
	int		status;

	i = 0;
	cmd = data->cmds;
	status = 0;
	signal(SIGINT, cmd_sigint);
	while (cmd)
	{
		wait(&status);
		if (!is_builtin(cmd->cmd_params[0]))
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_code = WTERMSIG(status) + 128;
		}
		cmd = cmd->next;
	}
	signals();
}

void	exec_pipeline(t_data *data)
{
	int		input_fd;
	t_cmd	*cmd;
	int		pipe_fd[2];

	input_fd = 0;
	cmd = data->cmds;
	while (cmd)
	{
		if (!cmd->next)
		{
			exec_last(data, cmd, input_fd);
			break ;
		}
		pipe(pipe_fd);
		exec_child(data, cmd, input_fd, pipe_fd);
		input_fd = pipe_fd[0];
		cmd = cmd->next;
	}
	wait_all(data);
}
