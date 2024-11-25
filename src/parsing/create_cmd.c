/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:30:43 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/25 15:44:47 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Ebauche de free
void	free_cmds(t_cmd **list)
{
	t_cmd	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		ft_free_tab(tmp->cmd_args);
		*list = tmp;
	}
	list = NULL;
}

void	print_cmd_list(t_cmd *list)
{
	int	i;

	while (list)
	{
		i = 0;
		while (list->cmd_args[i])
			printf("%s\n", list->cmd_args[i++]);
		list = list->next;
	}
}

void	create_cmd_list(t_data *data, t_token *token)
{
	t_token	*head;
	t_cmd	*cmd;

	cmd = NULL;
	data->cmds = cmd;
	head = token;
	while (token && token->next != head)
	{
		if (token->type == CMD)
		{
			append_cmd(&data->cmds, get_cmd_args(&token), -2, -2);
		}
		token = token->next;
	}
	if (token->type == CMD)
		append_cmd(&data->cmds, get_cmd_args(&token), -2, -2);
	// print_cmd_list(data->cmds);
	// free_cmds(&data->cmds);
}
