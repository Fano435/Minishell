/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:12:35 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/18 14:56:45 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list **list)
{
	t_list	*current;
	t_list	*tmp;

	current = *list;
	while (current && current->next)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free(current);
	return ;
}

void	print_list(t_list *list)
{
	while (list)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
	}
}

t_list	*sort_list(t_list *list)
{
	t_list	*start;
	t_list	*next;
	char	*str;

	if (!list)
		return (NULL);
	start = list;
	while (list)
	{
		next = list->next;
		while (next)
		{
			if (ft_strcmp(list->content, next->content) > 0)
			{
				str = list->content;
				list->content = next->content;
				next->content = str;
			}
			next = next->next;
		}
		list = list->next;
	}
	return (start);
}
