/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:19:53 by jrasamim          #+#    #+#             */
/*   Updated: 2024/05/23 17:19:15 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/*void	testf(unsigned int i, char *c)
{
	*c = *c + i;
}
int	main()
{
	char	ex[] = "Version originale";
	ft_striteri(ex, testf);
	printf("%s\n", ex);
}*/
