/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:53:03 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/17 16:12:02 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

t_env	*lstnew(char *content, int index)
{
	t_env	*newlist;

	newlist = malloc(sizeof(t_env));
	if (newlist == NULL)
		return (NULL);
	newlist->var = ft_strdup(content);
	newlist->index = index;
	newlist->next = NULL;
	newlist->prev = NULL;
	return (newlist);
}

void	lstadd_back(t_env **lstenv, t_env *newnode)
{
	t_env	*curr;
	
	curr = *lstenv;
	if (!*lstenv)
	{
		*lstenv = newnode;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = newnode;
	newnode->prev = curr;
}
