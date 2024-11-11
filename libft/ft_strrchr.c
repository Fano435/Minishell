/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:54:22 by jrasamim          #+#    #+#             */
/*   Updated: 2024/05/28 14:38:21 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	int		i;
	char	*last;

	i = 0;
	last = NULL;
	while (str[i])
	{
		if (str[i] == (char) c)
			last = &str[i];
		i++;
	}
	if (str[i] == (char) c)
		last = &str[i];
	return (last);
}
