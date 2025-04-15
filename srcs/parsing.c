/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:54:15 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/15 20:44:38 by tiaperei         ###   ########.fr       */
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
			break ;
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
	build_command(args_list);
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
		if (line[*i] == '\'')
			(*i)++;
	}
	else
	{
		(*i)++;
		while (line[*i] && line[*i] != '"')
			(*i)++;
		arg = ft_substr(line, start, (*i) - start);
		append_node(args_list, arg, DOUBLE_QUOTE);
		if (line[*i] == '"')
			(*i)++;
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

void	build_command(t_args_list **args_list)
{
	t_args_list	*current;
	t_command	*first_cmd;
	t_command	*current_cmd;

	current = *args_list;
	first_cmd = NULL;
	current_cmd = NULL;
	while (current)
	{
		if (!current_cmd || token_is_pipe(current->content))
		{
			append_new_command(&first_cmd, &current_cmd);
			if (token_is_pipe(current->content))
			{
				current = current->next;
				continue ;
			}
		}
		if (token_is_redirection(current->content))
			handle_redirection(current_cmd, &current, first_cmd);
		else
			add_argument(current_cmd, current->content, first_cmd);
		current = current->next;
	}
}

void	append_new_command(t_command **first_cmd, t_command **current_cmd)
{
	t_command	*new_cmd;

	new_cmd = init_command();
	if (!new_cmd)
		free_command(first_cmd);
	if (!(*first_cmd))
		*first_cmd = new_cmd;
	else
		(*current_cmd)->next = new_cmd;
	*current_cmd = new_cmd;
}

void	add_argument(t_command *cmd, char *content, t_command *first_cmd)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) + cmd->count_args + 2);
	if (!new_args)
		free_command(&first_cmd);
	i = 0;
	while (i < cmd->count_args)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[cmd->count_args] = content;
	new_args[cmd->count_args + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	cmd->count_args++;
}
