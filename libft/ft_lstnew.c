/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:15:55 by jrasamim          #+#    #+#             */
/*   Updated: 2024/11/14 17:08:56 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*el;

	el = malloc(sizeof(t_list));
	if (!el)
		return (NULL);
	el->content = content;
	// el->content = ft_strdup(content);
	// if (!el->content)
	// 	return (NULL);
	el->next = NULL;
	return (el);
}
