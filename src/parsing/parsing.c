/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:25:29 by idjakovi          #+#    #+#             */
/*   Updated: 2024/12/30 19:11:29 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_db_quotes(char *s, int i, t_data *data)
{
	char	*str_db_q;
	char	*temp;

	i++;
	str_db_q = ft_strdup("\"");
	while (s[i] != '\"')
	{
		temp = str_db_q;
		if (s[i] == '$')
		{
			if (!norm_if_db_q(s, i))
				str_db_q = handle_var_env_db_quotes(s, str_db_q, &i, data);
			else if (s[i + 1] == '?')
				str_db_q = handle_exit_status(str_db_q, &i, data);
			else if (!cond_handle_dollar(s, i))
				str_db_q = handle_dollar(s, str_db_q, &i);
		}
		else
			str_db_q = handle_char_db_quotes(s, str_db_q, &i);
		free(temp);
	}
	temp = str_db_q;
	str_db_q = ft_strjoin(str_db_q, "\"");
	free(temp);
	return (str_db_q);
}

bool	is_valid_char(char c)
{
	if (c != ' ' && c != '\"' && c != '\'' && c != '$' && c != '?' && c != '\0'
		&& c != '=')
		return (true);
	return (false);
}

char	*parse_no_quotes(char *str, int i, t_data *data)
{
	char	*str_no_q;
	char	*temp;

	str_no_q = ft_strdup("");
	while (str[i] != '\"' && str[i] != '\'' && str[i] != '\0')
	{
		temp = str_no_q;
		if (str[i] == '$')
		{
			if (is_valid_char(str[i + 1]))
				str_no_q = handle_var_env_no_quotes(str, str_no_q, &i, data);
			else if (str[i + 1] == '?')
				str_no_q = handle_exit_status(str_no_q, &i, data);
			else if (str[i + 1] == ' ' || str[i + 1] == '\0' || str[i
				+ 1] == '$' || str[i + 1] == '=')
				str_no_q = handle_dollar(str, str_no_q, &i);
			else if (str[i + 1] == '\"' || str[i + 1] == '\'')
				break ;
		}
		else
			str_no_q = handle_char_no_quotes(str, str_no_q, &i);
		free(temp);
	}
	return (str_no_q);
}

char	*update_str_parsed(char *(*parser)(char *, int, t_data *), char *str,
		char *str_parsed, int i, t_data *data)
{
	char	*temp;
	char	*old_parsed;

	temp = parser(str, i, data);
	old_parsed = str_parsed;
	str_parsed = ft_strjoin(str_parsed, temp);
	free(old_parsed);
	free(temp);
	return (str_parsed);
}

char	*parse_rl(char *str, t_data *data)
{
	int		i;
	char	*str_parsed;

	if (!str)
		return (NULL);
	i = 0;
	str_parsed = ft_strdup("");
	if (check_closed_quotes(str) || check_full_w_s(str))
		return (str_parsed);
	while (str[i])
	{
		if (str[i] == '\'')
			str_parsed = update_str_parsed(parse_sing_quotes, str, str_parsed,
					i, data);
		else if (str[i] == '\"')
			str_parsed = update_str_parsed(parse_db_quotes, str, str_parsed, i,
					data);
		else
			str_parsed = update_str_parsed(parse_no_quotes, str, str_parsed, i,
					data);
		i = advance(str, i, str[i]);
	}
	return (str_parsed);
}
