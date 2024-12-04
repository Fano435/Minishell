/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:36:42 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/04 16:52:15 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *lim)
{
	char	*here_doc;
	int		tmp_fd;

	tmp_fd = open("tmp.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (1)
	{
		here_doc = readline("heredoc> ");
		if (ft_strcmp(here_doc, lim) == 0)
		{
			free(here_doc);
			close(tmp_fd);
			return ;
		}
		if (ft_strcmp(here_doc, lim) != 0)
		{
			write(tmp_fd, here_doc, ft_strlen(here_doc));
			write(tmp_fd, "\n", 1);
			free(here_doc);
		}
	}
}
