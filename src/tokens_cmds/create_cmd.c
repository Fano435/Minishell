/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:30:43 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/23 15:57:17 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_cmd(t_data *data, t_token **token)
{
	append_cmd(&data->cmds, get_cmd_params(data, token), -2, -2);
	get_infile(data, token);
	get_outfile(data, token);
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
			create_cmd(data, &token);
		if (token->prev->type != ARG && token->prev->type != CMD
			&& token->type == HEREDOC)
			here_doc(token->next->str);
		token = token->next;
	}
	if (token->type == CMD)
		create_cmd(data, &token);
	if (token->prev->type != ARG && token->prev->type != CMD
		&& token->type == HEREDOC)
		here_doc(token->next->str);
}
