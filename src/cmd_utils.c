/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:21:38 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/22 18:00:08 by jrasamim         ###   ########.fr       */
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
	new->cmd_args = args;
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
