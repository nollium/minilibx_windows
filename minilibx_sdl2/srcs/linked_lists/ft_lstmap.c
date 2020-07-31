/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:09:26 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/31 17:53:56 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_lists.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *dst;
	t_list *dst_next;

	if (!*f || !lst || !(dst = ft_lstnew((*f)(lst->content))))
		return (NULL);
	dst_next = dst;
	while (lst->next)
	{
		if (!(dst_next->next = ft_lstnew((*f)(lst->next->content))))
		{
			ft_lstclear(&dst, del);
			return (NULL);
		}
		if (dst_next->next->content == NULL)
		{
			ft_lstclear(&dst, del);
			return (NULL);
		}
		lst = lst->next;
		dst_next = dst_next->next;
	}
	return (dst);
}
