/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:05:06 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/12 18:57:47 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	received_signal;

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

	received_signal = fork();
	if (received_signal == 0)
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
	return (login);
}

int	main(void)
{
	char	*rl;
	char	**args;
	int		pipe_fd[2];
	char	*header;

	signals();
	header = header_prompt();
	while (1)
	{
		printf("%d", received_signal);
		rl = readline(header);
		if (rl == NULL)
			break ;
		add_history(rl);
		args = ft_split(rl, ' ');
		pipe(pipe_fd);
		exec(args, pipe_fd);
		wait(NULL);
		received_signal = 0;
	}
	rl_clear_history();
	return (0);
}
