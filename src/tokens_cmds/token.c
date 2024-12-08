/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:34:40 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/08 18:12:45 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ordre important d'abord les doubles
int	is_operator(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(str, "<", 1) == 0)
		return (INPUT);
	if (ft_strncmp(str, ">", 1) == 0)
		return (TRUNC);
	if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	return (0);
}

int	add_operator(t_token **token_list, char **line)
{
	int	op;

	op = is_operator(*line);
	if (!line || !op)
		return (0);
	if (op == INPUT)
		append_token(token_list, ft_strdup("<"), INPUT);
	else if (op == HEREDOC)
		append_token(token_list, ft_strdup("<<"), HEREDOC);
	else if (op == TRUNC)
		append_token(token_list, ft_strdup(">"), TRUNC);
	else if (op == APPEND)
		append_token(token_list, ft_strdup(">>"), APPEND);
	else if (op == PIPE)
		append_token(token_list, ft_strdup("|"), PIPE);
	if ((op == INPUT || op == TRUNC || op == PIPE))
	{
		if (**line)
			(*line)++;
	}
	else if (**line)
		(*line) += 2;
	return (1);
}

int	is_delimitor(char c)
{
	if (c == '\0' || c == ' ')
		return (1);
	return (0);
}

int	word_len(char *str, int *quotes)
{
	int	i;

	i = 0;
	*quotes = 0;
	while (!is_delimitor(str[i]) && !is_operator(str + i))
	{
		if (str[i] == '\"')
		{
			(*quotes)++;
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			i++;
		}
		if (str[i] == '\'')
		{
			(*quotes)++;
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
		}
		i++;
	}
	return (i);
}

void	add_word(t_token **token_list, char **line)
{
	int		length;
	char	*word;
	int		quotes;

	quotes = 0;
	length = word_len(*line, &quotes);
	if (!length)
		return ;
	word = malloc((length + 1 - (quotes * 2)) * sizeof(char));
	if (!word)
		return (print_error(ERR_MALLOC));
	copy_token(*line, word, length);
	append_token(token_list, word, 0);
	*line += length - 1;
}

void	create_token_list(t_data *data, char *line)
{
	t_token	*token_head;

	if (!line)
		return ;
	token_head = NULL;
	data->tokens = token_head;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (!add_operator(&data->tokens, &line))
			add_word(&data->tokens, &line);
		if (*line)
			line++;
	}
	assign_words_type(&data->tokens);
	if (!check_syntax(&data->tokens))
	{
		free_tokens(&data->tokens);
		data->tokens = NULL;
	}
}
