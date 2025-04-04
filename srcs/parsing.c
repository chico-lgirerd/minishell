/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:54:15 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/04 17:22:42 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "split.h"
#include "color.h"
#include "utils.h"

void	parsing_args(t_args_list **args_list, char *line)
{
	char	**args;
	int		i;

	args = split(line, " \f\n\r\t\v");
	if (!args)
		ft_error(RED"malloc in split failed"RESET);
	i = 0;
	while (args[i])
	{
		append_node(args_list, ft_strdup(args[i]));
		i++;
	}
	free_args(args);
}

void	append_node(t_args_list **args, char *content)
{
	t_args_list	*node;
	t_args_list	*last_node;

	node = malloc(sizeof(t_args_list));
	if (!node)
		perror(RED"malloc in append_node failed"RESET);
	node->next = NULL;
	node->prev = NULL;
	node->content = content;
	if (!(*args))
		*args = node;
	else
	{
		last_node = ft_lstlast(*args);
		last_node->next = node;
		node->prev = last_node;
	}
}

