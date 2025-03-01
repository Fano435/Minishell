/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:45:18 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/30 13:50:49 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	var_exist(char *env, char *str)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if ((int)ft_strlen(str) == i && ft_strncmp(env, str, i) == 0
		&& env[i] == '=')
		return (true);
	return (false);
}

char	*find_var(t_list **lst, char *str)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (var_exist(tmp->content, str))
			return (ft_strdup(tmp->content));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_var_value(char *var)
{
	int		i;
	char	*value;

	i = 0;
	if (!var || !ft_strchr(var, '='))
		return (NULL);
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i + 1])
		return (NULL);
	value = ft_strdup(&var[i + 1]);
	free(var);
	return (value);
}

int	copy_env(t_data *data, char **env)
{
	int		i;
	t_list	*my_env;
	t_list	*tmp;

	i = 0;
	if (!env)
		return (0);
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
	data->tokens = NULL;
	data->cmds = NULL;
	data->exit_code = 0;
	signals();
}
