/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:14:00 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/14 15:48:47 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_lists.h"
#include <stdlib.h>

t_list	*ft_lstcpy(t_list *lst, void (*del)(void *))
{
	t_list *dst;
	t_list *dst_next;

	if (!(dst = ft_lstnew(lst->content)))
		return (NULL);
	dst_next = dst;
	while (lst->next)
	{
		if (!(dst_next->next = ft_lstnew(lst->next->content)))
		{
			ft_lstclear(&dst, del);
			return (NULL);
		}
		lst = lst->next;
		dst_next = dst_next->next;
	}
	return (dst);
}
