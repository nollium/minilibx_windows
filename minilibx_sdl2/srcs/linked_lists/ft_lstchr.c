/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:39:19 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/31 18:46:27 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_lists.h"

int	ft_lstchr(t_list *lst, void *find)
{
	while (lst)
	{
		if (find == lst->content)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
