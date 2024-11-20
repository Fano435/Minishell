/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:05:06 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/20 19:19:19 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal;

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

	g_signal = fork();
	if (g_signal == 0)
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
	char	**args;
	int		pipe_fd[2];
	t_data	data;

	init_data(ac, av, env, &data);
	while (1)
	{
		rl = readline("minishell > ");
		if (rl == NULL)
			break ;
		create_tokens(&data, rl);
		print_tokens(data.tokens);
		add_history(rl);
		args = ft_split(rl, ' ');
		if (is_builtin(args[0]))
			exec_builtin(&data, args[0], &args[1]);
		else
		{
			pipe(pipe_fd);
			exec(args, pipe_fd);
			wait(NULL);
		}
		g_signal = 0;
	}
	rl_clear_history();
	return (0);
}
