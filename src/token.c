/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:34:40 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/20 19:25:16 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	add_operator(t_token **token_list, char **str)
{
	int	op;

	op = is_operator(*str);
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
		(*str)++;
	else
		*str += 2;
}

void	create_tokens(t_data *data, char *line)
{
	t_token	*token_head;
	int		i;

	token_head = NULL;
	data->tokens = token_head;
	i = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		add_operator(&data->tokens, &line);
		line++;
	}
}

void	print_tokens(t_token *token)
{
	t_token	*head;

	head = token;
	while (token && token->next != head)
	{
		printf("%s\n", token->str);
		token = token->next;
	}
	printf("%s\n", token->str);
}
