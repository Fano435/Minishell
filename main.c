/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:05:06 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/11 19:34:47 by jrasamim         ###   ########.fr       */
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

void	exec(char **args, int pipe_fd[2])
{
	char	*cmd;
	char	**paths;

	if (fork() == 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		paths = ft_split(getenv("PATH"), ':');
		cmd = extract_cmd(paths, args[0]);
		if (!cmd)
			exit(EXIT_FAILURE);
		execve(cmd, args, NULL);
	}
}

int	main(void)
{
	char	*rl;
	char	**args;
	int		pipe_fd[2];
	int		status;

	// afficher le nom de la machine, le repertoire courant +
	// "$" si utilisateur normal || "#" si admin root
	rl = readline("[MINISHELL] ~ $ ");
	args = ft_split(rl, ' ');
	pipe(pipe_fd);
	exec(args, pipe_fd);
	wait(&status);
	printf("%d\n", status);
	rl_clear_history();
	return (0);
}
