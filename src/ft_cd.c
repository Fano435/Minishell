/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:31:26 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/15 19:28:54 by jrasamim         ###   ########.fr       */
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
		tmp->content = pwd;
	}
}

void	ft_cd(t_data *data, char *path)
{
	if (path == NULL)
		path = getenv("HOME");
	g_signal = chdir(path);
	if (g_signal == -1)
	{
		perror("cd");
		return ;
	}
	update_wd(data, "OLDPWD=");
	update_wd(data, "PWD=");
}
