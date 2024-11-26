/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idjakovi <idjakovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:34:30 by idjakovi          #+#    #+#             */
/*   Updated: 2024/11/25 19:56:59 by idjakovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_to_quotes(char *str, int i, char c)
{
	i++;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0')
	{
		printf("error\n");
		exit(1);
	}
	if (str[i] == c)
		i++;
	return (i);
}

int	check_closed_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i = skip_to_quotes(str, i, '\'');
		if (str[i] == '\"')
			i = skip_to_quotes(str, i, '\"');
		if (str[i] != '\'' && str[i] != '\"' && str[i] != '\0')
		{
			while (str[i] != '\'' && str[i] != '\"' && str[i] != '\0')
				i++;
		}
	}
	return (0);
}

int	advance(char *str, int i, char c)
{
	if (c == '\'' || c == '\"')
	{
		i++;
		while (str[i] != c)
			i++;
		i++;
	}
	else
	{
		i++;
		while (str[i] != '\"' && str[i] != '\'' && str[i] != '\0')
			i++;
	}
	return (i);
}

char	*handle_dollar(char *str, char *substr, int *i)
{
	int		start;
	char	*temp;

	start = *i;
	(*i)++;
	temp = ft_substr(str, start, *i - start);
	substr = ft_strjoin(substr, temp);
	free(temp);
	return (substr);
}
