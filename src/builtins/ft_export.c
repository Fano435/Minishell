/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:45:35 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/02 17:04:51 by jrasamim         ###   ########.fr       */
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
		i++;
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
		if (ft_strncmp(content, var, size) == 0 && var[size] == '\0')
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
	while (tmp && i < pos)
	{
		tmp = tmp->next;
		i++;
	}
	tmp->content = ft_strdup(value);
}

void	ft_export(t_data *data, char **params)
{
	int		pos;
	t_list	*new_var;

	if (!params[1])
		return (export_no_args(data));
	params++;
	while (*params)
	{
		pos = var_pos(data->env, *params);
		if (!valid_identifier(*params))
		{
			print_error("not a valid identifier\n");
			data->exit_code = 1;
		}
		else if (pos >= 0)
			update_env(&data->env, pos, *params);
		else if (pos == -1)
		{
			new_var = ft_lstnew(*params);
			if (!new_var)
			{
				print_error(ERR_MALLOC);
				data->exit_code = 1;
				break ;
			}
			ft_lstadd_back(&data->env, new_var);
		}
		params++;
	}
}
