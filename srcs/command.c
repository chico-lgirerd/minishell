/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:55 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/29 12:33:27 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "utils.h"

static void	append_new_command(t_command **first_cmd, t_command **current_cmd)
{
	t_command	*new_cmd;

	new_cmd = init_command();
	//new_cmd = NULL;
	if (!new_cmd)
	{
		//free_all_data
		//free_command(first_cmd);
		exit(EXIT_FAILURE);
	}
	if (!(*first_cmd))
		*first_cmd = new_cmd;
	else
		(*current_cmd)->next = new_cmd;
	*current_cmd = new_cmd;
}

static void	update_redirection(t_command *cmd, char *type, char *file)
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

static void	handle_redirection(t_command *cmd, t_args **current)
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

static void	add_argument(t_command *cmd, char *content, t_command *first_cmd)
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
