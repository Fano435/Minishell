/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:45:35 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/19 20:00:12 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	export_no_args(t_data *data)
{
	t_list	*sorted;

	sorted = sort_list(data->env);
	if (!sorted)
		return (1);
	while (sorted)
	{
		printf("declare -x ");
		print_dbl_quotes(sorted->content);
		sorted = sorted->next;
	}
	return (0);
}

static void	update_env(t_list **env, int pos, char *value)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *env;
	while (tmp && i < pos)
	{
		tmp = tmp->next;
		i++;
	}
	tmp->content = ft_strdup(value);
}

static int	add_to_env(t_data *data, char *var)
{
	t_list	*new_var;

	new_var = ft_lstnew(var);
	if (!new_var)
	{
		print_error(ERR_MALLOC);
		return (1);
	}
	ft_lstadd_back(&data->env, new_var);
	return (0);
}

int	ft_export(t_data *data, char **params)
{
	int	pos;
	int	code;

	if (!params[1])
		return (export_no_args(data));
	code = 0;
	params++;
	while (*params)
	{
		pos = var_pos(data->env, *params);
		if (!valid_identifier(*params))
		{
			print_error("not a valid identifier\n");
			code = 1;
		}
		else if (pos >= 0)
			update_env(&data->env, pos, *params);
		else if (pos == -1)
			code = add_to_env(data, *params);
		params++;
	}
	return (code);
}
