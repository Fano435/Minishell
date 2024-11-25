/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:52:36 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/25 18:44:01 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(char *file)
{
	int	in;

	in = -1;
	if (access(file, R_OK) != 0)
		perror(file);
	in = open(file, O_RDONLY);
	// if (in >= 0)
	// {
	// 	dup2(in, STDIN_FILENO);
	// 	close(in);
	// }
	return (in);
}

int	get_infile(t_data *data, t_token **token)
{
	t_token	*tmp;

	tmp = (*token)->prev;
	if (tmp->type == INPUT)
		return (open_infile(tmp->prev->str));
	if (tmp->type == PIPE)
		return (data->pipe[0]);
	return (0);
}

int	open_outfile(t_data *data, char *file, int type)
{
	int	out;

	out = -1;
	if (access(file, W_OK) != 0)
		perror(file);
	if (type == TRUNC)
		out = open(file, O_WRONLY | O_CREAT | O_TRUNC);
	if (type == APPEND)
		out = open(file, O_WRONLY | O_CREAT | O_APPEND);
	if (type == PIPE)
		out = data->pipe[1];
	// if (out >= 0)
	// {
	// 	dup2(out, STDOUT_FILENO);
	// 	close(out);
	// }
	return (out);
}

void	fill_fds(t_data *data, t_cmd *cmd, t_token **tokken)
{
	t_token	*tmp;

	tmp = *tokken;
	while (tmp && tmp->next->type == ARG)
		tmp = tmp->next;
	if (!tmp->next)
		cmd->outfile = STDOUT_FILENO;
	else
		cmd->outfile = open_outfile(data, tmp->next->str, tmp->next->type);
}
