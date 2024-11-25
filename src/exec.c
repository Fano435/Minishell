/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:55:33 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/25 18:53:35 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_cmd(char **paths, char *str)
{
	int		i;
	char	*path;
	char	*cmd;

	i = 0;
	while (str && paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return (NULL);
		cmd = ft_strjoin(path, str);
		if (!cmd)
			return (NULL);
		free(path);
		if (access(cmd, F_OK | X_OK) == 0)
		{
			ft_free_tab(paths);
			return (cmd);
		}
		free(cmd);
		i++;
	}
	if (paths)
		ft_free_tab(paths);
	return (NULL);
}

char	*get_path(t_data *data, char *cmd)
{
	char	*path_env;
	char	**paths;

	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = get_var_value(find_var(&data->env, "PATH"));
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	return (extract_cmd(paths, cmd));
}

void	exec(t_data *data, t_cmd *cmd)
{
	char	*path;

	if (cmd->skip_cmd)
		exit(EXIT_FAILURE);
	path = get_path(data, cmd->cmd_params[0]);
	if (!path)
	{
		write(2, "Command not found\n", 19);
		exit(EXIT_FAILURE);
	}
	execve(path, cmd->cmd_params, NULL);
	free(path);
}

void	exec_last(t_data *data, t_cmd *cmd, int input_fd)
{
	if (fork() == 0)
	{
		if (cmd->outfile != -1)
		{
			dup2(cmd->outfile, STDOUT_FILENO);
			close(cmd->outfile);
		}
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
		exec(data, cmd);
		exit(EXIT_FAILURE);
	}
	close(input_fd);
}

void	exec_pipeline(t_data *data)
{
	int		*pipe_fd;
	int		input_fd;
	t_cmd	*cmd;

	input_fd = 0;
	pipe_fd = data->pipe;
	cmd = data->cmds;
	while (cmd && cmd->next)
	{
		pipe(pipe_fd);
		if (fork() == 0)
		{
			if (cmd->infile != -1)
			{
				dup2(cmd->infile, STDIN_FILENO);
				close(cmd->infile);
			}
			if (cmd->outfile != -1)
			{
				dup2(cmd->outfile, STDOUT_FILENO);
				close(cmd->outfile);
			}
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exec(data, cmd);
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]);
		input_fd = pipe_fd[0];
		cmd = cmd->next;
	}
	exec_last(data, cmd, input_fd);
}
