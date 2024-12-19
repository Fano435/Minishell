/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:00:24 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/19 19:14:15 by jrasamim         ###   ########.fr       */
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

long	atol_exit(char *str, bool *valid)
{
	long	res;
	int		sign;
	int		i;
	int		start;

	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	start = i;
	while (str[i] && ft_isdigit(str[i]))
		res = res * 10 + (str[i++] - '0');
	if (i - start > 19 || start == i || res < 0)
		*valid = false;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i])
		*valid = false;
	return (sign * res);
}

int	ft_exit(char **params)
{
	int		n;
	bool	valid;

	valid = true;
	if (!params[1])
		return (0);
	n = atol_exit(params[1], &valid);
	if (valid && ft_tablen(params) > 2)
	{
		print_error("too many arguments\n");
		return (2);
	}
	else if (!valid)
	{
		print_error("numeric argument required\n");
		return (2);
	}
	return (manage_negs(n));
}
