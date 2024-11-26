/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idjakovi <idjakovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:25:29 by idjakovi          #+#    #+#             */
/*   Updated: 2024/11/26 14:45:24 by idjakovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_sing_quotes(char *str, int i)
{
	int		start;
	char	*str_sing_quotes;

	i++;
	start = i;
	while (str[i] != '\'')
		i++;
	str_sing_quotes = ft_substr(str, start, i - start);
	return (str_sing_quotes);
}

char	*parse_db_quotes(char *str, int i)
{
	char	*str_db_quotes;
	char	*temp;

	i++;
	str_db_quotes = ft_strdup("");
	while (str[i] != '\"')
	{
		temp = str_db_quotes;
		if (str[i] == '$')
		{
			if (str[i + 1] != ' ' && str[i + 1] != '\"' && str[i + 1] != '\''
				&& str[i + 1] != '$' && str[i + 1] != '?')
				str_db_quotes = handle_var_env_db_quotes(str, str_db_quotes,
						&i);
			else if (str[i + 1] == '?')
				handle_exit_status(&i);
			else if (str[i + 1] == '\'' || str[i + 1] == '\"' || str[i
				+ 1] == ' ')
				str_db_quotes = handle_dollar(str, str_db_quotes, &i);
		}
		else
			str_db_quotes = handle_char_db_quotes(str, str_db_quotes, &i);
		free(temp);
	}
	return (str_db_quotes);
}

char	*parse_no_quotes(char *str, int i)
{
	char	*str_no_quotes;
	char	*temp;

	str_no_quotes = ft_strdup("");
	while (str[i] != '\"' && str[i] != '\'' && str[i] != '\0')
	{
		temp = str_no_quotes;
		if (str[i] == '$')
		{
			if (str[i + 1] != ' ' && str[i + 1] != '\"' && str[i + 1] != '\''
				&& str[i + 1] != '$' && str[i + 1] != '?' && str[i + 1] != '\0')
				str_no_quotes = handle_var_env_no_quotes(str, str_no_quotes,
						&i);
			else if (str[i + 1] == '?')
				handle_exit_status(&i);
			else if (str[i + 1] == '\'' || str[i + 1] == '\"' || str[i
				+ 1] == ' ' || str[i + 1] == '\0')
				str_no_quotes = handle_dollar(str, str_no_quotes, &i);
		}
		else
			str_no_quotes = handle_char_no_quotes(str, str_no_quotes, &i);
		free(temp);
	}
	return (str_no_quotes);
}

char	*update_str_parsed(char *(*parser)(char *, int), char *str,
		char *str_parsed, int i)
{
	char	*temp;
	char	*old_parsed;

	temp = parser(str, i);
	old_parsed = str_parsed;
	str_parsed = ft_strjoin(str_parsed, temp);
	free(old_parsed);
	free(temp);
	return (str_parsed);
}

char	*parse_rl(char *str)
{
	int		i;
	char	*str_parsed;

	i = 0;
	check_closed_quotes(str);
	str_parsed = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
			str_parsed = update_str_parsed(parse_sing_quotes, str, str_parsed,
					i);
		else if (str[i] == '\"')
			str_parsed = update_str_parsed(parse_db_quotes, str, str_parsed, i);
		else
			str_parsed = update_str_parsed(parse_no_quotes, str, str_parsed, i);
		i = advance(str, i, str[i]);
	}
	return (str_parsed);
}
