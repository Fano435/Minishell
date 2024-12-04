/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:52:36 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/04 16:59:08 by jrasamim         ###   ########.fr       */
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
	if (type == HEREDOC)
	{
		here_doc(file);
		if (access("tmp.txt", R_OK) != 0)
			perror("tmp.txt");
		fd = open("tmp.txt", O_RDONLY);
	}
	if (type == TRUNC)
	{
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (access(file, W_OK) != 0)
			perror(file);
	}
	if (type == APPEND)
	{
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (access(file, W_OK) != 0)
			perror(file);
	}
	return (fd);
}

void	get_outfile(t_data *data, t_token **token)
{
	t_token	*tmp;
	t_cmd	*cmd;

	cmd = ft_cmdlast(data->cmds);
	tmp = *token;
	while (tmp && tmp->next != data->tokens && (tmp->next->type != CMD))
	{
		if (tmp->type == TRUNC || tmp->type == APPEND)
		{
			cmd->outfile = open_file(tmp->next->str, tmp->type);
			if (cmd->outfile == ERR_FILE_OPEN)
				cmd->skip_cmd = true;
			break ;
		}
		tmp = tmp->next;
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
