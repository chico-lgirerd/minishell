/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:33:16 by tiaperei          #+#    #+#             */
/*   Updated: 2024/11/14 20:02:41 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clean_newlist(t_list *newlist, void (*del)(void *), void *(content))
{
	del(content);
	ft_lstclear(&newlist, del);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*tmp;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (content == NULL)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		tmp = ft_lstnew(content);
		if (tmp == NULL)
		{
			clean_newlist(newlist, del, content);
			return (NULL);
		}
		ft_lstadd_back(&newlist, tmp);
		lst = lst->next;
	}
	return (newlist);
}
