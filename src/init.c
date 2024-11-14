/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:45:18 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/14 17:31:49 by jrasamim         ###   ########.fr       */
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

char	*find_var(t_list **lst, char *str)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strnstr(tmp->content, str, ft_strlen(str)))
			return (ft_strdup(tmp->content));
		tmp = tmp->next;
	}
	return (NULL);
}

int	copy_env(t_data *data, char **env)
{
	int		i;
	t_list	*my_env;
	t_list	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_lstnew(env[i]);
		if (!tmp)
			free_list(&my_env);
		if (i == 0)
			my_env = tmp;
		else
			ft_lstadd_back(&my_env, tmp);
		i++;
	}
	data->env = my_env;
	return (1);
}

void	init_data(int ac, char **av, char **env, t_data *data)
{
	(void)ac;
	(void)av;
	copy_env(data, env);
	signals();
}
