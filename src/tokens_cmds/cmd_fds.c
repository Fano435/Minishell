/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:52:36 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/27 16:24:27 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_data *data, char *file, int type)
{
	int	fd;

	(void)data;
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
		if (access(".tmp", R_OK) != 0)
			return (ERR_FILE_OPEN);
		fd = open(".tmp", O_RDONLY);
	}
	return (fd);
}

int	open_outfile(char *file, int type)
{
	int	fd;

	fd = NO_FD;
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
	while (tmp && tmp != data->tokens && (tmp->prev->type != PIPE))
		tmp = tmp->prev;
	while (tmp && tmp->next != data->tokens && (tmp->type != PIPE))
	{
		if (tmp->type == TRUNC || tmp->type == APPEND)
		{
			if (cmd->outfile >= 0)
				close(cmd->outfile);
			cmd->outfile = open_outfile(tmp->next->str, tmp->type);
			if (cmd->outfile == ERR_FILE_OPEN)
			{
				cmd->skip_cmd = true;
				return ;
			}
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
	while (tmp && tmp != data->tokens && (tmp->prev->type != PIPE))
		tmp = tmp->prev;
	while (tmp && tmp->next != data->tokens && (tmp->type != PIPE))
	{
		if (tmp->type == INPUT || tmp->type == HEREDOC)
		{
			if (cmd->infile >= 0)
				close(cmd->infile);
			cmd->infile = open_infile(data, tmp->next->str, tmp->type);
			if (cmd->infile == ERR_FILE_OPEN)
			{
				cmd->skip_cmd = true;
				return ;
			}
		}
		tmp = tmp->next;
	}
}
