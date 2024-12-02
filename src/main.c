/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:05:06 by jrasamim          #+#    #+#             */
/*   Updated: 2024/12/02 17:41:26 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal;

char	*header_prompt(void)
{
	char	curr_dir[1024];
	char	*login;

	login = getenv("USER");
	ft_strlcat(login, "@~", ft_strlen(login) + 3);
	getcwd(curr_dir, sizeof(curr_dir));
	if (ft_strcmp(getenv("USER"), "root") == 0)
		ft_strlcat(curr_dir, "# ", sizeof(curr_dir));
	else
		ft_strlcat(curr_dir, "$ ", sizeof(curr_dir));
	ft_strlcat(login, curr_dir, sizeof(curr_dir));
	return (ft_strdup(login));
}

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

void	wait_all(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = data->cmds;
	while (cmd)
	{
		wait(NULL);
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*rl;
	char	*parsed;
	t_data	data;

	(void)parsed;
	init_data(ac, av, env, &data);
	while (1)
	{
		rl = readline("minishell > ");
		if (rl == NULL)
			break ;
		parsed = parse_rl(rl, &data);
		create_token_list(&data, parsed);
		create_cmd_list(&data, data.tokens);
		// print_tokens(data.tokens);
		// print_cmd_list(data.cmds);
		exec_pipeline(&data);
		wait_all(&data);
		g_signal = 0;
		free_tokens(&data.tokens);
		free_cmds(&data.cmds);
		free(parsed);
		add_history(rl);
	}
	rl_clear_history();
	free_env(&data.env);
	return (0);
}
