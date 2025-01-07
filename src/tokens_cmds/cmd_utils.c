/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:21:38 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/27 15:51:03 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	t_cmd	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

t_cmd	*new_cmd(char **args, int infile, int outfile)
{
	t_cmd	*new;

	if (!args)
		return (NULL);
	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		free(args);
		return (NULL);
	}
	new->skip_cmd = false;
	new->infile = infile;
	new->outfile = outfile;
	new->cmd_params = args;
	new->pid = -1;
	new->next = NULL;
	return (new);
}

void	append_cmd(t_cmd **cmd_list, char **args, int infile, int outfile)
{
	t_cmd	*new;
	t_cmd	*last;

	last = ft_cmdlast(*cmd_list);
	new = new_cmd(args, infile, outfile);
	if (!new)
		return ;
	if (!*cmd_list)
		*cmd_list = new;
	else
		last->next = new;
}

int	count_params(t_token **token)
{
	t_token	*tmp;
	int		i;

	i = 1;
	tmp = (*token)->next;
	while (tmp && tmp->type == ARG)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**get_cmd_params(t_data *data, t_token **token)
{
	char	**params;
	t_token	*current;
	int		len;
	int		i;

	current = *token;
	(void)data;
	i = 0;
	len = count_params(token);
	params = malloc((len + 1) * sizeof(char *));
	if (!params)
		return (NULL);
	while (current && i < len)
	{
		params[i] = ft_strdup(current->str);
		if (!params[i])
		{
			ft_free_tab(params);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	params[i] = NULL;
	return (params);
}
