/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:44:59 by jrasamim          #+#    #+#             */
/*   Updated: 2024/05/24 15:34:13 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size <= dstlen)
		return (srclen + size);
	i = 0;
	if (size < dstlen + srclen + 1)
		size--;
	while (src[i] && i + dstlen < size)
	{
		dst[i + dstlen] = src[i];
		i++;
	}
	dst[i + dstlen] = '\0';
	return (srclen + dstlen);
}

/*int	main()
{
	char	*src = "World";
	char	dst[10] = "Hello";
	size_t	res = ft_strlcat(dst, src, 9);
	printf("%zu\n", res);
	printf("%s\n", dst);
}*/
