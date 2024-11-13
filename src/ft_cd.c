/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:31:26 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/13 18:39:02 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *path, char *header)
{
	char	cwd[1024];

	(void)header;
	if (path == NULL)
		path = getenv("HOME");
	g_signal = chdir(path);
	if (g_signal == -1)
		perror("cd");
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	printf("%s\n", getenv("PWD"));
}
