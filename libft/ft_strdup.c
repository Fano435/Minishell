/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:35:05 by jrasamim          #+#    #+#             */
/*   Updated: 2024/05/24 20:27:52 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	int		i;

	i = 0;
	while (s[i])
		i++;
	cpy = malloc(i * sizeof(char) + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

/*#include <stdio.h>
int	main()
{
	char *s1 = "Hello World";
	char *dup1 = ft_strdup(s1);
	printf("Original: %s\n", s1);
	printf("Duplicate: %s\n", dup1);
	free(dup1);
}*/
