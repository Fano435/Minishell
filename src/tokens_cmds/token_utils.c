/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:52:12 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/31 16:39:53 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_token **token_list)
{
	t_token	*head;
	t_token	*token;

	token = *token_list;
	if (!token)
		return (1);
	head = token;
	if (token->type == PIPE)
		return (0);
	while (token && token->next && token->next != head)
	{
		if ((is_operator(token->str) && token->type != PIPE)
			&& (token->next == head || is_operator(token->next->str)))
			return (0);
		token = token->next;
	}
	if (is_operator(token->str))
		return (0);
	return (1);
}

void	assign_words_type(t_token **list)
{
	t_token	*head;
	t_token	*token;

	token = *list;
	if (!token)
		return ;
	head = token;
	if (!token->type)
	{
		token->type = CMD;
		token = token->next;
	}
	while (token && token->next != head)
	{
		if (!token->type && (token->prev->type == CMD
				|| token->prev->type == ARG))
			token->type = ARG;
		if (!token->type && !(token->prev->type && token->prev->type != PIPE))
			token->type = CMD;
		token = token->next;
	}
	if (!token->type && !(token->prev->type && token->prev->type != PIPE))
		token->type = CMD;
	if (!token->type && (token->prev->type == CMD || token->prev->type == ARG))
		token->type = ARG;
}

void	copy_double_quotes(char *str, char *word, int *i, int *j)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		word[(*j)++] = str[*i];
		(*i)++;
	}
}

void	copy_single_quotes(char *str, char *word, int *i, int *j)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		word[(*j)++] = str[*i];
		(*i)++;
	}
}

void	copy_token(char *str, char *word, int len)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!word)
		return ;
	while (str[i] && i < len)
	{
		if (str[i] == '\"')
			copy_double_quotes(str, word, &i, &j);
		else if (str[i] == '\'')
			copy_single_quotes(str, word, &i, &j);
		else
			word[j++] = str[i];
		i++;
	}
	word[j] = '\0';
}
