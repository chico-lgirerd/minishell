/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:54:15 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/05 14:23:34 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"
#include "split.h"
#include "color.h"
#include "utils.h"

void	parsing_args(t_args_list **args_list, char *line)
{
	char	*arg;
	int		i;
	int		start;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break;
		start = i;
		if (line[i] == '\'' || line[i] == '"')
			parsing_quote(args_list, line, ++start, &i);
		else
		{
			while (line[i] && !ft_isspace(line[i])
				&& line[i] != '\'' && line[i] != '"')
			i++;
			arg = ft_substr(line, start, i - start);
			append_node(args_list, arg, NO_QUOTE);
		}
	}
}

void	parsing_quote(t_args_list **args_list, char *line, int start, int *i)
{
	char	*arg;
	
	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		arg = ft_substr(line, start, (*i) - start);
		append_node(args_list, arg, SINGLE_QUOTE);
	}
	else
	{
		(*i)++;
		while (line[*i] && line[*i] != '"')
			(*i)++;
		arg = ft_substr(line, start, (*i) - start);
		append_node(args_list, arg, DOUBLE_QUOTE);
	}
}

void	append_node(t_args_list **args, char *content, int quote)
{
	t_args_list	*node;
	t_args_list	*last_node;

	node = malloc(sizeof(t_args_list));
	if (!node)
		perror(RED"malloc in append_node failed"RESET);
	node->next = NULL;
	node->prev = NULL;
	node->content = content;
	node->in_quote = quote;
	if (!(*args))
		*args = node;
	else
	{
		last_node = ft_lstlast(*args);
		last_node->next = node;
		node->prev = last_node;
	}
}

