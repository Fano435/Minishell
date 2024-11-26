/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:30:43 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/26 18:04:49 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_list(t_cmd *list)
{
	int	i;

	while (list)
	{
		i = 0;
		while (list->cmd_params[i])
			printf("%s\n", list->cmd_params[i++]);
		list = list->next;
	}
}

void	create_cmd_list(t_data *data, t_token *token)
{
	t_token	*head;
	t_cmd	*cmd;

	if (!token)
		return ;
	cmd = NULL;
	data->cmds = cmd;
	head = token;
	while (token && token->next != head)
	{
		if (token->type == CMD)
		{
			append_cmd(&data->cmds, get_cmd_params(&token), -2, -2);
			// get_outfile(data, &token);
			// printf("%d\n", cmd->outfile);
		}
		token = token->next;
	}
	if (token->type == CMD)
	{
		append_cmd(&data->cmds, get_cmd_params(&token), -2, -2);
		// get_outfile(data, cmd, &token);
	}
}
