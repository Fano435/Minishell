/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:52:36 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/26 18:06:44 by jrasamim         ###   ########.fr       */
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
	(void)data;
	if (type == PIPE)
	{
		// printf("%d\n", data->pipe[1]);
		return (out);
	}
	if (type == TRUNC)
		out = open(file, O_WRONLY | O_CREAT | O_TRUNC);
	if (type == APPEND)
		out = open(file, O_WRONLY | O_CREAT | O_APPEND);
	if (access(file, W_OK) != 0)
		perror(file);
	// if (out >= 0)
	// {
	// 	dup2(out, STDOUT_FILENO);
	// 	close(out);
	// }
	return (out);
}

void	get_outfile(t_data *data, t_token **token)
{
	t_token	*tmp;
	t_cmd	*cmd;

	cmd = ft_cmdlast(data->cmds);
	tmp = *token;
	while (tmp && tmp->next->type == ARG)
		tmp = tmp->next;
	// printf("%s\n", tmp->str);
	// printf("%s\n", data->tokens->str);
	printf("%s\n", *cmd->cmd_params);
	if (cmd && tmp != data->tokens)
	{
		printf("%d\n", open_outfile(data, tmp->next->str, tmp->type));
		cmd->outfile = open_outfile(data, tmp->next->str, tmp->type);
	}
}
