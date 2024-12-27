/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:51:53 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/23 15:53:06 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *token)
{
	t_token	*head;

	if (!token)
		return ;
	head = token;
	while (token && token->next != head)
	{
		printf("%s : %d\n", token->str, token->type);
		token = token->next;
	}
	printf("%s : %d\n", token->str, token->type);
}

void	print_cmd_list(t_cmd *list)
{
	int	i;

	while (list)
	{
		i = 0;
		printf("Infile : %d\nOutfile : %d\n", list->infile, list->outfile);
		while (list->cmd_params[i])
			printf("%s\n\n", list->cmd_params[i++]);
		list = list->next;
	}
}
