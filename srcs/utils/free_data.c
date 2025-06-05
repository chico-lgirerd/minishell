/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:45:28 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/05 18:53:09 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cmd.h"
#include "colors.h"
#include "libft.h"

void	free_all_data(t_data *data, bool free_env)
{
	if (data->args_list)
		free_args_list(&data->args_list);
	if (data->first_cmd)
		free_command(&data->first_cmd);
	if (free_env && data->env)
	{
		free_env_list(data->env);
		data->env = NULL;
	}
	if (data->forks.pids)
	{
		free(data->forks.pids);
		data->forks.pids = NULL;
	}
	if (data->forks.pipes)
	{
		close_free_pipes(data->forks.pipes, data->forks.num_cmds - 1);
		data->forks.pipes = NULL;
	}
	ft_memset(data, 0, sizeof(t_data));
}

void	free_args_list(t_args **args_list)
{
	t_args	*tmp;
	t_args	*current;

	if (!args_list || !(*args_list))
		return ;
	current = *args_list;
	while (current)
	{
		tmp = current->next;
		if (current->content)
		{
			free(current->content);
			current->content = NULL;
		}
		free(current);
		current = tmp;
	}
	*args_list = NULL;
}

static void	free_command_redirection(t_command *cmd)
{
	t_redir	*tmp;
	t_redir	*curr;

	if (!cmd)
		return ;
	curr = cmd->out_redir;
	while (curr)
	{
		tmp = curr->next;
		if (curr->filename)
			free(curr->filename);
		free(curr);
		curr = tmp;
	}
	free_heredocs(cmd);
	free(cmd->input_file);
}

void	free_command(t_command **first_cmd)
{
	t_command	*tmp;
	t_command	*current;
	int			i;

	if (!first_cmd || !(*first_cmd))
		return ;
	current = *first_cmd;
	while (current)
	{
		tmp = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				free(current->args[i]);
				i++;
			}
			free(current->args);
		}
		free_command_redirection(current);
		free(current);
		current = tmp;
	}
	*first_cmd = NULL;
}

void	ft_error(t_data *data, char *str, int errcode)
{
	free_all_data(data, true);
	ft_putstr_fd(RED"minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(RESET, 2);
	exit(errcode);
}
