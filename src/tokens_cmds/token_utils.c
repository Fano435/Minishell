/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:52:12 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/04 17:34:12 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_words_type(t_token *token)
{
	t_token	*head;

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
		if (!token->type && token->prev->type == PIPE)
			token->type = CMD;
		if (!token->type && (token->prev->type == CMD
				|| token->prev->type == ARG))
			token->type = ARG;
		token = token->next;
	}
	if (!token->type && token->prev->type == PIPE)
		token->type = CMD;
	if (!token->type && (token->prev->type == CMD || token->prev->type == ARG))
		token->type = ARG;
}

void	print_tokens(t_token *token)
{
	t_token	*head;

	if (!token)
		return ;
	head = token;
	while (token && token->next != head)
	{
		printf("%s : %d\n", token->str, token->type);
		token = token->next;
	}
	printf("%s : %d\n", token->str, token->type);
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
		word[j++] = str[i];
		i++;
	}
	word[j] = '\0';
}

t_token	*new_tokken(char *str, int type)
{
	t_token	*new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(str);
		return (NULL);
	}
	new->str = str;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	append_token(t_token **tokken_list, char *str, int type)
{
	t_token	*new;

	new = new_tokken(str, type);
	if (!new)
		return ;
	if (!*tokken_list)
	{
		*tokken_list = new;
		(*tokken_list)->next = *tokken_list;
		(*tokken_list)->prev = *tokken_list;
	}
	else
	{
		new->prev = (*tokken_list)->prev;
		new->next = (*tokken_list);
		(*tokken_list)->prev->next = new;
		(*tokken_list)->prev = new;
	}
}
