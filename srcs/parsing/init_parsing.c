/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:45:31 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/21 15:12:17 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include "libft.h"

void	init_data(t_data *data, char **env)
{
	data->env = init_env(env);
	if (!data->env)
		ft_error(data, "failed to init env", 12);
	data->line = NULL;
	data->exit_value = 0;
	data->quote = 0;
	data->arg = NULL;
	data->expanded_arg = NULL;
	data->original_tab = NULL;
	data->last_pos = 0;
	data->last_expand = false;
	data->args_list = NULL;
	data->first_cmd = NULL;
	data->forks.pids = NULL;
	data->forks.pipes = NULL;
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->heredoc_fd = -2;
	return (cmd);
}

void	init_redir(t_data *data, t_command *cmd, char *file, int append)
{
	t_redir	*redir;
	t_redir	**curr;

	(void)file;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		ft_error(data, "malloc: failed in init_redir", errno);
	redir->filename = ft_strdup(file);
	if (!redir->filename)
	{
		free(redir);
		ft_error(data, "malloc: failed in init_redir", errno);
	}
	redir->append = append;
	redir->next = NULL;
	curr = &cmd->out_redir;
	while (*curr)
		curr = &(*curr)->next;
	*curr = redir;
}

t_env	*init_env(char **env)
{
	int		i;
	t_env	*head;
	t_env	*curr;

	i = 0;
	curr = NULL;
	head = curr;
	while (env[i])
	{
		curr = lstnew(env[i], i);
		if (!curr)
			return (NULL);
		lstadd_back(&head, curr);
		curr = curr->next;
		i++;
	}
	return (head);
}
