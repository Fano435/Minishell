/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:02:02 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/03 19:46:40 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	check_newline(char *arg)
{
	size_t	j;

	if (arg[0] == '-')
	{
		j = 1;
		while (arg[j])
		{
			if (arg[j] != 'n')
				break ;
			j++;
		}
		if (j == ft_strlen(arg) && j != 1)
			return (1);
	}
	return (0);
}

int	ft_echo(char **params)
{
	int	newline;
	int	i;
	int	len;

	newline = 1;
	i = 1;
	len = ft_tablen(params) - 1;
	while (params[i] && check_newline(params[i]))
	{
		newline = 0;
		i++;
	}
	while (params[i])
	{
		write(1, params[i], ft_strlen(params[i]));
		if (i != len)
			write(1, " ", 2);
		i++;
	}
	if (newline)
		write(1, "\n", 2);
	return (0);
}
