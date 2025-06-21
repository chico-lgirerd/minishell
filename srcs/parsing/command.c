/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:55 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/21 18:09:16 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include "libft.h"

#include <stdio.h>

static void	append_new_command(t_data *data, t_command **current_cmd)
{
	t_command	*new_cmd;

	new_cmd = init_command();
	if (!new_cmd)
		ft_error(data, "malloc: failed in append_new_command", errno);
	if (!(data->first_cmd))
		data->first_cmd = new_cmd;
	else
		(*current_cmd)->next = new_cmd;
	*current_cmd = new_cmd;
}

static void	handle_redirection(t_data *data, t_command *cmd, t_args **current)
{
	char	*type;
	char	*file;

	type = (*current)->content;
	(*current) = (*current)->next;
	file = (*current)->content;
	cmd->has_redirection = true;
	if (ft_strcmp(type, "<") == 0)
	{
		free(cmd->input_file);
		cmd->input_file = ft_strdup(file);
	}
	if (ft_strcmp(type, ">") == 0)
		init_redir(data, cmd, file, 0);
	if (ft_strcmp(type, "<<") == 0)
		add_heredoc(data, cmd, file);
	if (ft_strcmp(type, ">>") == 0)
		init_redir(data, cmd, file, 1);
}

static void	add_argument(t_data *data, t_command *cmd, char *content)
{
	char	**new_args;
	int		i;

	(void)content;
	new_args = malloc(sizeof(char *) * (cmd->count_args + 2));
	if (!new_args)
		ft_error(data, "malloc: failed in add_argument", errno);
	i = 0;
	while (i < cmd->count_args)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[cmd->count_args] = ft_strdup(content);
	if (!new_args[cmd->count_args])
	{
		free(new_args);
		ft_error(data, "malloc: failed in add_argument", errno);
	}
	new_args[cmd->count_args + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	cmd->count_args++;
}

void	build_command(t_data *data, t_args *args_list)
{
	t_args		*current;
	t_command	*cmd;

	current = args_list;
	cmd = NULL;
	while (current)
	{
		if (!cmd || (token_is_pipe(current->content) && current->op_valid))
		{
			append_new_command(data, &cmd);
			if (token_is_pipe(current->content) && current->op_valid)
			{
				current = current->next;
				continue ;
			}
		}
		if (token_is_redirection(current->content) && current->op_valid)
			handle_redirection(data, cmd, &current);
		else
			add_argument(data, cmd, current->content);
		current = current->next;
	}
}
