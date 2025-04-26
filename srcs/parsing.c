/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:54:15 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/26 15:56:49 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"
#include "color.h"
#include "utils.h"

void	parsing_args(t_args **args_list, char *line)
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
}

void	parsing_quote(t_args **args_list, char *line, int s, int *i/*,  char **env */)
{
	char	*arg;

	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		arg = ft_substr(line, s, (*i) - s);
		append_node(args_list, arg, SINGLE_QUOTE);
		if (line[*i] == '\'')
			(*i)++;
	}
	else
	{
		(*i)++;
		while (line[*i] && line[*i] != '"')
			(*i)++;
		arg = ft_substr(line, s, (*i) - s);
		append_node(args_list, arg, DOUBLE_QUOTE);
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

t_command	*build_command(t_args **args_list)
{
	t_args		*current;
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
			handle_redirection(current_cmd, &current);
		else
			add_argument(current_cmd, current->content, first_cmd);
		current = current->next;
	}
	return (first_cmd);
}

void	append_new_command(t_command **first_cmd, t_command **current_cmd)
{
	t_command	*new_cmd;

	new_cmd = init_command();
	if (!new_cmd)
	{
		free_command(first_cmd);
		return ;
	}
	if (!(*first_cmd))
		*first_cmd = new_cmd;
	else
		(*current_cmd)->next = new_cmd;
	*current_cmd = new_cmd;
}

void	handle_redirection(t_command *cmd, t_args **current)
{
	char	*type;
	char	*file;

	type = (*current)->content;
	(*current) = (*current)->next;
	if (!(*current))
		return ;
	file = (*current)->content;
	update_redirection(cmd, type, file);
}

void	update_redirection(t_command *cmd, char *type, char *file)
{
	if (ft_strcmp(type, "<") == 0)
	{
		if (cmd->input_file)
			free(cmd->input_file);
		cmd->input_file = ft_strdup(file);
	}
	if (ft_strcmp(type, ">") == 0)
	{
		if (cmd->output_file)
			free(cmd->output_file);
		cmd->output_file = ft_strdup(file);
		cmd->append_output = 0;
	}
	if (ft_strcmp(type, "<<") == 0)
	{
		if (cmd->heredoc_delimiter)
			free(cmd->heredoc_delimiter);
		cmd->heredoc_delimiter = ft_strdup(file);
	}
	if (ft_strcmp(type, ">>") == 0)
	{
		if (cmd->output_file)
			free(cmd->output_file);
		cmd->output_file = ft_strdup(file);
		cmd->append_output = 1;
	}
}

void	add_argument(t_command *cmd, char *content, t_command *first_cmd)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (cmd->count_args + 2));
	if (!new_args)
		free_command(&first_cmd);
	i = 0;
	while (i < cmd->count_args)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[cmd->count_args] = ft_strdup(content);
	new_args[cmd->count_args + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	cmd->count_args++;
}
