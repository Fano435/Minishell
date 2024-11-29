/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:52:36 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/29 17:54:25 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *file, int type)
{
	int	fd;

	fd = NO_FD;
	if (type == PIPE)
		return (fd);
	if (type == INPUT)
	{
		if (access(file, R_OK) != 0)
			perror(file);
		fd = open(file, O_RDONLY);
	}
	if (type == TRUNC)
	{
		if (access(file, W_OK) != 0)
			perror(file);
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	if (type == APPEND)
	{
		if (access(file, W_OK) != 0)
			perror(file);
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	return (fd);
}

void	get_outfile(t_data *data, t_token **token)
{
	t_token	*tmp;
	t_cmd	*cmd;

	cmd = ft_cmdlast(data->cmds);
	tmp = *token;
	while (tmp && tmp->next->type == ARG)
		tmp = tmp->next;
	if (tmp->next != data->tokens && (tmp->next->type == TRUNC
			|| tmp->next->type == APPEND))
	{
		tmp = tmp->next;
		cmd->outfile = open_file(tmp->next->str, tmp->type);
		if (cmd->outfile == ERR_FILE_OPEN)
			cmd->skip_cmd = true;
	}
}

void	get_infile(t_data *data, t_token **token)
{
	t_token	*tmp;
	t_cmd	*cmd;

	cmd = ft_cmdlast(data->cmds);
	tmp = *token;
	if (tmp->next->type == INPUT || tmp->next->type == HEREDOC)
	{
		tmp = tmp->next;
		cmd->infile = open_file(tmp->next->str, tmp->type);
		if (cmd->outfile == ERR_FILE_OPEN)
			cmd->skip_cmd = true;
	}
}
