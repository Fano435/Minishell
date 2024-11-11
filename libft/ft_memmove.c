/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:47:36 by jrasamim          #+#    #+#             */
/*   Updated: 2024/05/27 16:14:53 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmpd;
	unsigned char	*tmps;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	tmpd = (unsigned char *) dest;
	tmps = (unsigned char *) src;
	i = 0;
	if (tmpd > tmps)
	{
		while (n-- > 0)
			tmpd[n] = tmps[n];
	}
	else
	{
		while (i < n)
		{
			tmpd[i] = tmps[i];
			i++;
		}
	}
	return (dest);
}

/*int	main()
{
	char src[] = "Bonjour";
	char dst[] = "Hola";

	ft_memmove(dst, src, 3);
	printf("%s", dst);
}*/
