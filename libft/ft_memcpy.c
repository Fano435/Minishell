/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:41:40 by jrasamim          #+#    #+#             */
/*   Updated: 2024/06/12 16:58:04 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tmpd;
	unsigned char	*tmps;

	if (!dest && !src)
		return (NULL);
	tmpd = (unsigned char *)dest;
	tmps = (unsigned char *)src;
	while (n > 0)
	{
		*tmpd++ = *tmps++;
		n--;
	}
	return (dest);
}
