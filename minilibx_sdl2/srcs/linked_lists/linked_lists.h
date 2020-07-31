/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:51:32 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/31 17:51:32 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LISTS_H
# define LINKED_LISTS_H

# include <stdlib.h>

typedef struct			s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

void    ft_lstadd_back(t_list **alst, t_list *new);
void    ft_lstadd_front(t_list **alst, t_list *new);
int     ft_lstchr(t_list *lst, void *find);
void    ft_lstclear(t_list **lst, void (*del)(void *));
t_list  *ft_lstcpy(t_list *lst, void (*del)(void *));
void    ft_lstdelone(t_list *lst, void (*del)(void *));
void    ft_lstiter(t_list *lst, void (*f)(void *));
t_list  *ft_lstlast(t_list *lst);
t_list  *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list  *ft_lstnew(void *content);
int     ft_lstsize(t_list *lst);

#endif