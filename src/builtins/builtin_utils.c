/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:01:23 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/19 19:58:47 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	var_pos(t_list *env, char *var)
{
	int		size;
	int		i;
	char	*content;
	t_list	*tmp;

	if (!env)
		return (-1);
	tmp = env;
	i = 0;
	while (tmp)
	{
		size = 0;
		content = (char *)tmp->content;
		while (content[size] && content[size] != '=')
			size++;
		if (ft_strncmp(content, var, size) == 0 && (var[size] == '\0'
				|| var[size] == '='))
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (-1);
}
