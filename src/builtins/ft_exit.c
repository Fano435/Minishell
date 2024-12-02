/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:00:24 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/02 17:08:17 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_negs(int n)
{
	if (n < 0)
		return (256 - (-n % 256));
	else
		return (n % 256);
}

void	ft_exit(t_data *data, char **params)
{
	int	i;

	printf("exit\n");
	(void)data;
	if (!params[1])
		exit(0);
	i = 0;
	if (params[1][0] == '-' || params[1][0] == '+')
		i++;
	while (params[1][i])
	{
		if (!ft_isdigit(params[1][i]))
		{
			print_error("numeric argument required\n");
			exit(2);
		}
		i++;
	}
	if (ft_tablen(params) > 2)
		return (print_error("too many arguments\n"));
	exit(manage_negs(ft_atoi(params[1])));
}
