/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:31:26 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/03 19:43:06 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
}

static void	update_wd(t_data *data, char *var)
{
	char	*pwd;
	char	buffer[PATH_MAX];
	char	*cwd;
	t_list	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strnstr(tmp->content, var, ft_strlen(var)))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (ft_strcmp(var, "PWD=") == 0)
		{
			getcwd(buffer, sizeof(buffer));
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
		if (!pwd)
			return (print_error(ERR_MALLOC));
		free(tmp->content);
		tmp->content = pwd;
	}
}

int	ft_cd(t_data *data, char **params)
{
	char	*path;

	if (ft_tablen(params) > 2)
	{
		print_error("Too many arguments\n");
		return (1);
	}
	path = params[1];
	if (path == NULL)
		path = get_var_value(find_var(&data->env, "HOME"));
	if (!path)
		return (1);
	g_signal = chdir(path);
	if (path != params[1])
		free(path);
	if (g_signal == -1)
	{
		perror("cd");
		return (1);
	}
	update_wd(data, "OLDPWD=");
	update_wd(data, "PWD=");
	return (0);
}
