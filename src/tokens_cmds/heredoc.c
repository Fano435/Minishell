/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:36:42 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/27 16:26:31 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_heredoc(int code)
{
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	g_signal = code;
}

void	here_doc(char *lim, t_data *data)
{
	char	*here_doc;
	char	*parsed;
	int		tmp_fd;

	tmp_fd = open("tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	signal(SIGINT, sig_heredoc);
	while (1)
	{
		here_doc = readline("> ");
		if (g_signal != 0)
			break ;
		if (!here_doc)
		{
			printf("warning: here-doc delimited by end-of-file (wanted '%s')\n",
				lim);
			break ;
		}
		if (ft_strcmp(here_doc, lim) == 0)
			break ;
		parsed = parse_rl(here_doc, data);
		write(tmp_fd, parsed, ft_strlen(parsed));
		write(tmp_fd, "\n", 1);
		free(parsed);
		free(here_doc);
	}
	g_signal = 0;
	free(here_doc);
	close(tmp_fd);
}
