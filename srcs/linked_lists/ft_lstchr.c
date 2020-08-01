/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:39:19 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/31 21:44:24 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_lists.h"

t_list *ft_lstchr(t_list *lst, void *find)
{
	while (lst)
	{
		if (find == lst->content)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
