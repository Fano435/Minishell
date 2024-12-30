/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:52:46 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/30 19:10:53 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_sing_quotes(char *str, int i, t_data *data)
{
	int		start;
	char	*str_sing_quotes;

	(void)data;
	start = i;
	i++;
	while (str[i] != '\'')
		i++;
	str_sing_quotes = ft_substr(str, start, (i + 1) - start);
	return (str_sing_quotes);
}

int	norm_if_db_q(char *s, int i)
{
	if (s[i + 1] != ' ' && s[i + 1] != '\"' && s[i + 1] != '\'' && s[i
			+ 1] != '$' && s[i + 1] != '?')
		return (0);
	return (1);
}

int	cond_handle_dollar(char *s, int i)
{
	if (s[i + 1] == '\'' || s[i + 1] == '\"' || s[i + 1] == ' ' || s[i
			+ 1] == '$' || s[i + 1] == '=')
		return (0);
	return (1);
}
