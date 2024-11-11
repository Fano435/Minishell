/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:35:04 by jrasamim          #+#    #+#             */
/*   Updated: 2024/05/28 13:39:55 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
		last->next = new;
}

/*void	print_list(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("%s\n",(char *) tmp->content);
		tmp = tmp->next;
	}
}

int	main()
{
	t_list	*list = NULL;
	t_list	*node;
	int	i = 0;
	char	*a = "HEY";

	while (i < 6)
	{
		node = ft_lstnew((void*) a);
		ft_lstadd_back(&list, node);
		i++;
	}
	print_list(list);
}*/
