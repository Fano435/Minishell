/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:51:36 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/19 19:40:14 by jrasamim         ###   ########.fr       */
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
		if (access(cmd, F_OK) == 0)
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

int	is_directory(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

void	exec(t_data *data, t_cmd *cmd)
{
	char	*path;

	if (cmd->skip_cmd)
		exit(EXIT_FAILURE);
	path = get_path(data, cmd->cmd_params[0]);
	if (!path)
	{
		print_error("command not found\n");
		exit(CMD_NOT_FOUND);
	}
	if (is_directory(path))
	{
		print_error(path);
		print_error(": Is a directory\n");
		free(path);
		exit(CMD_NO_EXEC);
	}
	if (access(path, X_OK) != 0)
	{
		perror(path);
		free(path);
		exit(CMD_NO_EXEC);
	}
	execve(path, cmd->cmd_params, NULL);
	exit(EXIT_FAILURE);
	free(path);
}
