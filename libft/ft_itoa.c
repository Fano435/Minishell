/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:26:15 by jrasamim          #+#    #+#             */
/*   Updated: 2024/05/27 11:10:29 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int		size;

	size = 0;
	if (n <= 0)
		size++;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char			*a;
	unsigned int	nbr;
	int				size;

	if (n < 0)
		nbr = -n;
	else
		nbr = n;
	size = get_size(n);
	a = malloc((size + 1) * sizeof(char));
	if (!a)
		return (NULL);
	a[size] = '\0';
	size--;
	while (size > 0)
	{
			a[size--] = nbr % 10 + '0';
			nbr /= 10;
	}
	if (n < 0)
		a[0] = '-';
	else
		a[0] = nbr % 10 + '0';
	return (a);
}

/*int	main()
{
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(9600));
	printf("%s\n", ft_itoa(0));
}*/
