/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:55 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/03 15:03:51 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "libft.h"
#include "utils.h"
#include "files.h"

static void	append_new_command(t_data *data, t_command **current_cmd)
{
	t_command	*new_cmd;

	new_cmd = init_command();
	if (!new_cmd)
	{
		ft_error(data, "malloc: failed append_new_command");
		exit(EXIT_FAILURE);
	}
	if (!(data->first_cmd))
		data->first_cmd = new_cmd;
	else
		(*current_cmd)->next = new_cmd;
	*current_cmd = new_cmd;
}

static void	update_redirection(t_command *cmd, char *type, char *file)
{
	if (ft_strcmp(type, "<") == 0)
	{
		free(cmd->input_file);
		cmd->input_file = ft_strdup(file);
	}
	if (ft_strcmp(type, ">") == 0)
		init_redir(cmd, file, 0);
	if (ft_strcmp(type, "<<") == 0)
		add_heredoc(cmd, file);
	if (ft_strcmp(type, ">>") == 0)
		init_redir(cmd, file, 1);
}

static void	handle_redirection(t_command *cmd, t_args **current)
{
	char	*type;
	char	*file;

	/* if (!(*current)->next || !(*current)->next->content
		|| (token_is_operator((*current)->next->content)
			&& !(*current)->next->in_quote))
	{
		if ((*current)->next->content)
			print_syntax_error((*current)->next->content, 2);
		else
			print_syntax_error((*current)->content, 2);
		cmd->has_error = true;
		data->exit_value = 2;
		return ;
	} */
	type = (*current)->content;
	(*current) = (*current)->next;
	file = (*current)->content;
	cmd->has_redirection = true;
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

void	build_command(t_data *data, t_args *args_list)
{
	t_args		*current;
	t_command	*cmd;

	current = args_list;
	cmd = NULL;
	while (current)
	{
		if (!cmd || (token_is_pipe(current->content) && !current->in_quote))
		{
			append_new_command(data, &cmd);
			if (token_is_pipe(current->content) && !current->in_quote)
			{
				current = current->next;
				continue ;
			}
		}
		if (token_is_redirection(current->content) && !current->in_quote)
			handle_redirection(cmd, &current);
		else
			add_argument(cmd, current->content, data->first_cmd);
		if (cmd->has_error)
			return (free_command(&data->first_cmd));
		current = current->next;
	}
}
