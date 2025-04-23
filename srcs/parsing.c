/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:54:15 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/23 17:26:50 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"
#include "split.h"
#include "color.h"
#include "utils.h"

void	parsing_args(t_data *data, char *line)
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
			break ;
		start = i;
		if (line[i] == '\'' || line[i] == '"')
			parsing_quote(data, line, ++start, &i);
		else
		{
			while (line[i] && !ft_isspace(line[i])
				&& line[i] != '\'' && line[i] != '"')
				i++;
			arg = ft_substr(line, start, i - start);
			append_node(&data->args_list, expand_arg(arg, data->env), NO_QUOTE);
			free(arg);
		}
	}
}

void	parsing_quote(t_data *data, char *line, int s, int *i)
{
	char	*arg;

	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		arg = ft_substr(line, s, (*i) - s);
		append_node(&data->args_list, arg, SINGLE_QUOTE);
		if (line[*i] == '\'')
			(*i)++;
	}
	else
	{
		(*i)++;
		while (line[*i] && line[*i] != '"')
			(*i)++;
		arg = ft_substr(line, s, (*i) - s);
		append_node(&data->args_list, expand_arg(arg, data->env), DOUBLE_QUOTE);
		free(arg);
		if (line[*i] == '"')
			(*i)++;
	}
}

void	append_node(t_args **args, char *content, int quote)
{
	t_args	*node;
	t_args	*last_node;

	node = malloc(sizeof(t_args));
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
