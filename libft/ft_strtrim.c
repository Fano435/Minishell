/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:44:56 by jrasamim          #+#    #+#             */
/*   Updated: 2024/06/05 18:01:20 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_trim(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i++])
			return (1);
	}
	return (0);
}

static char	*create_trimstr(char const *s1, size_t start, size_t len)
{
	char	*res;
	size_t	i;

	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s1[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (to_trim(s1[start], set))
		start++;
	while (to_trim(s1[end], set))
		end--;
	len = end - (start - 1);
	if (ft_strlen(s1) == 0 || len <= 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	return (create_trimstr(s1, start, len));
}

/*int	main(int ac, char *av[])
{
	printf("%s\n", ft_strtrim(av[ac-2], av[ac-1]));
}*/
