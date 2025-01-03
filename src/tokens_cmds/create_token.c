/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:40:37 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/31 16:40:55 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_tokken(char *str, int type)
{
	t_token	*new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(str);
		return (NULL);
	}
	new->str = str;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	append_token(t_token **tokken_list, char *str, int type)
{
	t_token	*new;

	new = new_tokken(str, type);
	if (!new)
		return ;
	if (!*tokken_list)
	{
		*tokken_list = new;
		(*tokken_list)->next = *tokken_list;
		(*tokken_list)->prev = *tokken_list;
	}
	else
	{
		new->prev = (*tokken_list)->prev;
		new->next = (*tokken_list);
		(*tokken_list)->prev->next = new;
		(*tokken_list)->prev = new;
	}
}
