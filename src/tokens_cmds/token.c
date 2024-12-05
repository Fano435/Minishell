/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:34:40 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/04 18:18:11 by jrasamim         ###   ########.fr       */
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

void	add_operator(t_token **token_list, char **line)
{
	int	op;

	op = is_operator(*line);
	if (!op)
		return ;
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
	if (op == INPUT || op == TRUNC || op == PIPE)
		(*line)++;
	else
		*line += 2;
}

int	word_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		i++;
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else
	{
		while (str[i] && str[i] != ' ' && !is_operator(str + i))
			i++;
	}
	return (i);
}

void	add_word(t_token **token_list, char **line)
{
	int		length;
	char	*word;

	length = word_len(*line);
	if (!length)
		return ;
	word = malloc((length + 1) * sizeof(char));
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
		add_operator(&data->tokens, &line);
		add_word(&data->tokens, &line);
		line++;
	}
	assign_words_type(data->tokens);
}
