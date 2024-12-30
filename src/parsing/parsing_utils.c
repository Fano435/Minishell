/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:27:11 by idjakovi          #+#    #+#             */
/*   Updated: 2024/12/30 16:30:17 by jrasamim         ###   ########.fr       */
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
	char	*line_var;
	char	*temp;
	int		start;

	(*i)++;
	start = *i;
	while (str[*i] != ' ' && str[*i] != '\"' && str[*i] != '$'
		&& str[*i] != '\'' && str[*i] != '\0')
		(*i)++;
	var_env = ft_substr(str, start, *i - start);
	line_var = find_var(&data->env, var_env);
	if (line_var != NULL)
		temp = get_var_value(line_var);
	else if (ft_strchr(var_env, '='))
	{
		while (*var_env != '=')
			var_env++;
		temp = ft_strdup(var_env);
		// free(var_env);
		// return (ft_strdup(""));
	}
	else
		temp = ft_strdup("");
	str_no_quotes = ft_strjoin(str_no_quotes, temp);
	free(temp);
	free(var_env);
	return (str_no_quotes);
}

char	*handle_var_env_db_quotes(char *str, char *str_db_quotes, int *i,
		t_data *data)
{
	char	*var_env;
	int		start;
	char	*line_var;
	char	*temp;

	(*i)++;
	start = *i;
	while (str[*i] != ' ' && str[*i] != '\"' && str[*i] != '\''
		&& str[*i] != '$')
		(*i)++;
	var_env = ft_substr(str, start, *i - start);
	line_var = find_var(&data->env, var_env);
	if (line_var != NULL)
		temp = get_var_value(line_var);
	else
	{
		free(var_env);
		return (ft_strdup("\""));
	}
	str_db_quotes = ft_strjoin(str_db_quotes, temp);
	free(temp);
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
