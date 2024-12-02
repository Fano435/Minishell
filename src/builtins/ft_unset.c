/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:32:19 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/02 16:48:01 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_list **env, int pos)
{
	t_list	*tmp;
	t_list	*curr;
	int		i;

	i = 0;
	curr = *env;
	if (pos == 0)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->content);
		free(tmp);
		return ;
	}
	while (curr && curr->next && i < pos - 1)
	{
		curr = curr->next;
		i++;
	}
	tmp = curr->next;
	curr->next = curr->next->next;
	free(tmp->content);
	free(tmp);
}

void	ft_unset(t_data *data, char **params)
{
	int	pos;

	if (params[1])
		params++;
	while (*params)
	{
		pos = var_pos(data->env, *params);
		if (pos != -1)
			delete_node(&data->env, pos);
		params++;
	}
	data->exit_code = 0;
}
