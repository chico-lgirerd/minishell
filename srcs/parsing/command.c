/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:55 by tiaperei          #+#    #+#             */
/*   Updated: 2025/05/18 15:28:37 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "libft.h"
#include "utils.h"
#include "files.h"

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

	if (!(*current)->next || !(*current)->next->content
		|| token_is_operator((*current)->next->content))
	{
		if ((*current)->next->content)
			printf("syntax error near unexpected token `%s'\n", (*current)->next->content);
		else
			printf("syntax error near unexpected token `%s'\n", (*current)->content);
		cmd->has_error = true;
		g_exit_value = 2;
		return ;
	}
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
		if (!cmd || (token_is_pipe(current->content) && !current->quoted))
		{
			append_new_command(&data->first_cmd, &cmd);
			if (token_is_pipe(current->content) && !current->quoted)
			{
				current = current->next;
				continue ;
			}
		}
		if (token_is_redirection(current->content) && !current->quoted)
			handle_redirection(cmd, &current);
		else
			add_argument(cmd, current->content, data->first_cmd);
		if (cmd->has_error)
			return (free_command(&data->first_cmd));
		current = current->next;
	}
}
