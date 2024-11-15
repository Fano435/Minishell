/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:45:35 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/15 20:22:30 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
	}
	return (true);
}

static void	print_dbl_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		printf("%c", str[i++]);
	if (str[i] && str[i] == '=')
		printf("=\"%s\"\n", &str[i + 1]);
	else
		printf("\n");
}

static void	export_no_args(t_data *data)
{
	t_list	*sorted;

	sorted = sort_list(data->env);
	while (sorted)
	{
		printf("declare -x ");
		print_dbl_quotes(sorted->content);
		sorted = sorted->next;
	}
}

int	var_pos(t_list *env, char *var)
{
	int		size;
	int		i;
	t_list	*tmp;

	if (!env)
		return (-1);
	size = 0;
	while (var[size] && var[size] != '=')
		size++;
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, size) == 0)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (-1);
}

void	update_env(t_list **env, int pos, char *value)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *env;
	while (env && i < pos)
	{
		tmp = tmp->next;
		i++;
	}
	tmp->content = ft_strdup(value);
}

void	ft_export(t_data *data, char **args)
{
	t_list	*new_var;
	int		pos;

	if (!args || !args[0])
		return (export_no_args(data));
	while (*args)
	{
		pos = var_pos(data->env, *args);
		printf("%s\n", *args);
		if (!valid_identifier(*args))
		{
			print_error("not a valid identifier\n");
			data->exit_code = 1;
		}
		else if (pos >= 0)
			update_env(&data->env, pos, *args);
		else if (pos == -1)
		{
			new_var = ft_lstnew(ft_strdup(*args));
			if (!new_var)
			{
				print_error(ERR_MALLOC);
				data->exit_code = 1;
				break ;
			}
			ft_lstadd_back(&data->env, new_var);
		}
		args++;
	}
}
