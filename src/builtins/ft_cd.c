/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:31:26 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/04 17:57:42 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (1);
}

t_list	*find_var_node(t_data *data, char *var)
{
	t_list	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strnstr(tmp->content, var, ft_strlen(var)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	update_wd(t_data *data, char *var)
{
	char	*pwd;
	char	buffer[PATH_MAX];
	char	*cwd;
	t_list	*tmp;

	tmp = find_var_node(data, var);
	if (!tmp)
		return ;
	if (ft_strcmp(var, "PWD=") == 0)
	{
		if (!getcwd(buffer, sizeof(buffer)))
			return ;
		pwd = ft_strjoin(var, buffer);
	}
	else
	{
		cwd = find_var(&data->env, "PWD");
		if (!cwd)
			return ;
		pwd = ft_strjoin("OLD", cwd);
		free(cwd);
	}
	free(tmp->content);
	tmp->content = pwd;
}

int	ft_cd(t_data *data, char **params)
{
	char	*path;
	int		success;

	if (ft_tablen(params) > 2)
		return (print_error("Too many arguments\n"));
	path = params[1];
	if (path == NULL)
		path = get_var_value(find_var(&data->env, "HOME"));
	if (!path)
		return (print_error("HOME not set\n"));
	success = chdir(path);
	if (path != params[1])
		free(path);
	if (success != 0)
	{
		perror(params[1]);
		return (1);
	}
	update_wd(data, "OLDPWD=");
	update_wd(data, "PWD=");
	return (0);
}
