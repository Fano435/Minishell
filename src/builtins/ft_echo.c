/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:02:02 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/30 15:06:08 by jrasamim         ###   ########.fr       */
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

int	ft_echo(char **args)
{
	int	i;
	int	len;
	int	newline;

	newline = 1;
	len = ft_tablen(args);
	i = 1;
	while (args[i] && check_newline(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		if (args[i][0] == '\'' || args[i][0] == '\"')
			write(1, args[i] + 1, ft_strlen(args[i]) - 2);
		else
			write(1, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
