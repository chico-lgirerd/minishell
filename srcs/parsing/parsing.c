/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:54:15 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/18 20:14:26 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "utils.h"

void	append_node(t_data *data, t_args **args,
	char *content, bool op_in_quote)
{
	t_args	*node;
	t_args	*last_node;

	if (!content)
		return ;
	node = malloc(sizeof(t_args));
	if (!node)
	{
		free(content);
		ft_error(data, "malloc: failed in append_node", 12);
	}
	node->next = NULL;
	node->prev = NULL;
	node->content = content;
	node->op_in_quote = op_in_quote;
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
		append_node(data, &data->args_list, ft_substr(line, (*i), 2), false);
		(*i) += 2;
		return (1);
	}
	if (line[*i] == '>' || line[*i] == '<' || line[*i] == '|')
	{
		append_node(data, &data->args_list, ft_substr(line, (*i), 1), false);
		(*i)++;
		return (1);
	}
	return (0);
}

static char	*parsing_quote(t_data *data, char *line, int start, int *i)
{
	char	quote;
	char	*sub_arg;

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	sub_arg = ft_substr(line, start, (*i) - start);
	if (!sub_arg)
	{
		free(data->arg);
		ft_error(data, "malloc: failed in parsing_quote", errno);
	}
	if (quote == '"')
	{
		expand_arg(data, sub_arg);
		free(sub_arg);
		sub_arg = data->expanded_arg;
	}
	if (line[*i] == quote)
		(*i)++;
	data->quote = 0;
	return (sub_arg);
}

static char	*parsing_no_quote(t_data *data, char *line, int start, int *i)
{
	char	*sub_arg;

	if (line[*i] == '$' && (line[*i + 1] == '\'' || line[*i + 1] == '"'))
	{
		start = ++(*i) + 1;
		return (parsing_quote(data, line, start, i));
	}
	while (line[*i] && !ft_isspace(line[*i])
		&& !char_is_quote(line[*i]) && !char_is_operator(line[*i])
		&& !(line[*i] == '$' && (line[*i + 1] == '\'' || line[*i + 1] == '"')))
		(*i)++;
	sub_arg = ft_substr(line, start, (*i) - start);
	if (!sub_arg)
	{
		free(data->arg);
		ft_error(data, "malloc: failed in parsing_no_quote", errno);
	}
	expand_arg(data, sub_arg);
	free(sub_arg);
	if (data->expanded_arg[0] == '\0')
	{
		free(data->expanded_arg);
		return (NULL);
	}
	return (data->expanded_arg);
}

void	parsing_args(t_data *data, char *line)
{
	int		i;
	int		start;
	char	*sub_arg;

	i = 0;
	while (line[i])
	{
		skip_space(line, &i);
		data->quote = update_quote_status(data, line[i]);
		if (!data->quote && append_operator(data, line, &i))
			continue ;
		data->arg = NULL;
		while (line[i] && !ft_isspace(line[i])
			&& (data->quote || !char_is_operator(line[i])))
		{
			start = i;
			if (char_is_quote(line[i]))
				sub_arg = parsing_quote(data, line, ++start, &i);
			else
				sub_arg = parsing_no_quote(data, line, start, &i);
			data->arg = strjoin_and_free(data->arg, sub_arg);
			data->quote = update_quote_status(data, line[i]);
		}
		append_node(data, &data->args_list, data->arg, true);
	}
}
