/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:36:42 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/30 18:09:13 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_heredoc(int code)
{
	unlink(".tmp");
	printf("\n");
	exit(code + 128);
}

void	child_here_doc(char *lim, t_data *data)
{
	char	*here_doc;
	char	*parsed;
	int		tmp_fd;

	tmp_fd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (tmp_fd < 0)
		exit(1);
	signal(SIGINT, sig_heredoc);
	while (1)
	{
		here_doc = readline("> ");
		if (!here_doc)
			break ;
		if (ft_strcmp(here_doc, lim) == 0)
			break ;
		parsed = parse_rl(here_doc, data);
		write(tmp_fd, parsed, ft_strlen(parsed));
		write(tmp_fd, "\n", 1);
		free(parsed);
		free(here_doc);
	}
	close(tmp_fd);
	exit(0);
}

int	here_doc(char *lim, t_data *data)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		child_here_doc(lim, data);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	signals();
	if (data->exit_code != 0)
		return (-1);
	return (0);
}
