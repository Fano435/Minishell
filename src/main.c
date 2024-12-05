/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:05:06 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/05 15:24:47 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal;

void	free_tokens(t_token **token)
{
	t_token	*tmp;
	t_token	*current;

	current = *token;
	if (!*token)
		return ;
	while (current && current->next != *token)
	{
		tmp = current->next;
		free(current->str);
		free(current);
		current = tmp;
	}
	tmp = current->next;
	free(current->str);
	free(current);
	current = tmp;
	token = NULL;
}

void	free_cmds(t_cmd **list)
{
	t_cmd	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->infile != NO_FD)
			close((*list)->infile);
		if ((*list)->outfile != NO_FD)
			close((*list)->outfile);
		ft_free_tab((*list)->cmd_params);
		free(*list);
		*list = tmp;
	}
	list = NULL;
}

void	free_env(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free((*list));
		*list = tmp;
	}
	list = NULL;
}

int	main(int ac, char **av, char **env)
{
	char	*rl;
	char	*parsed;
	t_data	data;

	init_data(ac, av, env, &data);
	while (1)
	{
		rl = readline("minishell > ");
		if (rl == NULL)
			break ;
		parsed = parse_rl(rl, &data);
		create_token_list(&data, parsed);
		create_cmd_list(&data, data.tokens);
		exec_pipeline(&data);
		g_signal = 0;
		free_tokens(&data.tokens);
		free_cmds(&data.cmds);
		free(parsed);
		unlink("tmp.txt");
		add_history(rl);
	}
	rl_clear_history();
	free_env(&data.env);
	return (0);
}
