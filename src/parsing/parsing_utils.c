/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:27:11 by idjakovi          #+#    #+#             */
/*   Updated: 2024/12/05 19:25:39 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_exit_status(char *str, int *i, t_data *data)
{
	char	*temp;

	(*i) += 2;
	temp = ft_itoa(data->exit_code);
	str = ft_strjoin(str, temp);
	free(temp);
	return (str);
}

char	*handle_var_env_no_quotes(char *str, char *str_no_quotes, int *i,
		t_data *data)
{
	char	*var_env;
	int		start;
	char	*temp;

	(*i)++;
	start = *i;
	while (str[*i] != ' ' && str[*i] != '\"' && str[*i] != '$'
		&& str[*i] != '\'' && str[*i] != '\0')
		(*i)++;
	var_env = ft_substr(str, start, *i - start);
	if (find_var(&data->env, var_env) != NULL)
	{
		str_no_quotes = ft_strjoin(str_no_quotes,
				get_var_value(find_var(&data->env, var_env)));
	}
	else
	{
		temp = ft_strdup("");
		str_no_quotes = ft_strjoin(str_no_quotes, temp);
		free(temp);
	}
	free(var_env);
	return (str_no_quotes);
}

char	*handle_var_env_db_quotes(char *str, char *str_db_quotes, int *i,
		t_data *data)
{
	char	*var_env;
	int		start;
	char	*temp;

	(*i)++;
	start = *i;
	while (str[*i] != ' ' && str[*i] != '\"' && str[*i] != '\''
		&& str[*i] != '$')
		(*i)++;
	var_env = ft_substr(str, start, *i - start);
	// jpeux pas tester mais normalement cest ca
	if (find_var(&data->env, var_env) != NULL)
	{
		str_db_quotes = ft_strjoin(str_db_quotes,
				get_var_value(find_var(&data->env, var_env)));
	}
	else
	{
		temp = ft_strdup("");
		str_db_quotes = ft_strjoin(str_db_quotes, temp);
		free(temp);
	}
	free(var_env);
	return (str_db_quotes);
}

char	*handle_char_no_quotes(char *str, char *str_no_quotes, int *i)
{
	int		start;
	char	*temp;

	start = *i;
	while (str[*i] != '$' && str[*i] != '\"' && str[*i] != '\''
		&& str[*i] != '\0')
		(*i)++;
	temp = ft_substr(str, start, *i - start);
	str_no_quotes = ft_strjoin(str_no_quotes, temp);
	free(temp);
	return (str_no_quotes);
}

char	*handle_char_db_quotes(char *str, char *str_db_quotes, int *i)
{
	int		start;
	char	*temp;

	start = *i;
	while (str[*i] != '$' && str[*i] != '\"')
		(*i)++;
	temp = ft_substr(str, start, *i - start);
	str_db_quotes = ft_strjoin(str_db_quotes, temp);
	free(temp);
	return (str_db_quotes);
}
