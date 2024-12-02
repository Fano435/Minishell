/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:31:14 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/02 17:03:40 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	char	cwd[PATH_MAX];

	// char	*cwd;
	// cwd = get_var_value(find_var(&data->env, "PWD"));
	// if (cwd)
	// {
	// 	printf("%s\n", cwd);
	// 	free(cwd);
	// }
	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
	}
	else
	{
		data->exit_code = 1;
	}
}
