/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:54:15 by tiaperei          #+#    #+#             */
/*   Updated: 2025/05/13 17:08:17 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"
#include "colors.h"
#include "colors.h"
#include "utils.h"

static void	append_node(t_args **args, char *content, bool quote)
{
	t_args	*node;
	t_args	*last_node;

	if (!content)
		return ;
	node = malloc(sizeof(t_args));
	if (!node)
	{
		perror(RED"malloc in append_node failed"RESET);
		free(content);
		exit(EXIT_FAILURE);
	}
	node->next = NULL;
	node->prev = NULL;
	node->content = content;
	node->quoted = quote;
	if (!(*args))
		*args = node;
	else
	{
		last_node = ft_lstlast(*args);
		last_node->next = node;
		node->prev = last_node;
	}
}

static int	append_operator(t_data *data, char *line, int *i)
{
	if ((line[*i] == '>' && line[*i + 1] == '>')
		|| (line[*i] == '<' && line[*i + 1] == '<'))
	{
		append_node(&data->args_list, ft_substr(line, (*i), 2), false);
		(*i) += 2;
		return (1);
	}
	if (line[*i] == '>' || line[*i] == '<' || line[*i] == '|')
	{
		append_node(&data->args_list, ft_substr(line, (*i), 1), false);
		(*i)++;
		return (1);
	}
	return (0);
}

static char	*parsing_quote(t_data *data, char *line, int start, int *i)
{
	char	*sub_arg;

	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		sub_arg = ft_substr(line, start, (*i) - start);
		if (line[*i] == '\'')
			(*i)++;
		return (sub_arg);
	}
	else
	{
		(*i)++;
		while (line[*i] && line[*i] != '"')
			(*i)++;
		sub_arg = ft_substr(line, start, (*i) - start);
		expand_arg(data, sub_arg);
		free(sub_arg);
		if (line[*i] == '"')
			(*i)++;
		return (data->expanded_arg);
	}
}

static char	*parsing_no_quote(t_data *data, char *line, int start, int *i)
{
	char	*sub_arg;

	if (line[*i] == '$' && (line[*i + 1] == '\'' || line[*i + 1] == '"'))
	{
		(*i)++;
		start = (*i) + 1;
		return (parsing_quote(data, line, start, i));
	}
	while (line[*i] && !ft_isspace(line[*i])
		&& !char_is_quote(line[*i]) && !char_is_operator(line[*i])
		&& !(line[*i] == '$' && (line[*i + 1] == '\'' || line[*i + 1] == '"')))
		(*i)++;
	sub_arg = ft_substr(line, start, (*i) - start);
	expand_arg(data, sub_arg);
	free(sub_arg);
	if (data->expanded_arg[0] == '\0')
		return (NULL);
	return (data->expanded_arg);
}

void	parsing_args(t_data *data, char *line)
{
	char	*arg;
	char	*sub_arg;
	int		i;
	int		start;

	i = 0;
	while (line[i])
	{
		skip_space(line, &i);
		update_quote_status(data, line[i]);
		if (!data->quote && append_operator(data, line, &i))
			continue ;
		arg = NULL;
		while (line[i] && !ft_isspace(line[i])
			&& (data->quote || !char_is_operator(line[i])))
		{
			start = i;
			if (char_is_quote(line[i]))
				sub_arg = parsing_quote(data, line, ++start, &i);
			else
				sub_arg = parsing_no_quote(data, line, start, &i);
			arg = strjoin_and_free(arg, sub_arg);
		}
		append_node(&data->args_list, arg, true);
	}
}
