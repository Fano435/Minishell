/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:00:24 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/19 17:38:12 by jrasamim         ###   ########.fr       */
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

void	ft_exit(t_data *data, char **args)
{
	int	i;
	int	n_args;

	printf("exit\n");
	(void)data;
	n_args = 0;
	if (!args || !args[0])
		exit(0);
	i = 0;
	if (args[0][0] == '-' || args[0][0] == '+')
		i++;
	while (args[0][i])
	{
		if (!ft_isdigit(args[0][i]))
		{
			print_error("numeric argument required\n");
			exit(2);
		}
		i++;
	}
	while (args[n_args])
		n_args++;
	if (n_args > 1)
		return (print_error("too many arguments\n"));
	exit(manage_negs(ft_atoi(args[0])));
}
