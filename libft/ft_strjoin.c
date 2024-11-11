/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:24:14 by jrasamim          #+#    #+#             */
/*   Updated: 2024/05/23 17:23:17 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	res = malloc((len_s1 + len_s2) * sizeof(char) + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len_s2)
	{
		res[i + len_s1] = s2[i];
		i++;
	}
	res[i + len_s1] = '\0';
	return (res);
}

/*int	main()
{
	char	*s1 = "World";
	char	*s2 = "Hello (Oui j'ai mis a l'envers)";
	char	*res = ft_strjoin(s1, s2);
	printf("%s\n", res);
}*/
