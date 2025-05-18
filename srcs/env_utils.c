/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:53:03 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/18 19:24:35 by lgirerd          ###   ########lyon.fr   */
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

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		if (env->var)
			free(env->var);
		free(env);
		env = temp;
	}
}

int	get_env_size(t_env *env)
{
	int		size;
	t_env	*curr;
	
	size = 0;
	curr = env;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

char	**env_to_array(t_env *env)
{
	char	**env_arr;
	int		i;
	t_env	*curr;
	
	env_arr = malloc(sizeof(char *) * (get_env_size(env) + 1));
	if (!env_arr)
		return (NULL);
	curr = env;
	i = 0;
	while (curr)
	{
		env_arr[i] = ft_strdup(curr->var);
		curr = curr->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
