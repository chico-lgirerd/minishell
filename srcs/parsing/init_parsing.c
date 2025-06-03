/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:45:31 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/03 16:57:57 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "colors.h"
#include "colors.h"
#include "libft.h"

void	init_data(t_data *data, char **env)
{
	data->env = init_env(env);
	// if (!data->env)
	// 	return ; passer init_data en int 
	data->line = NULL;
	data->exit_value = 0;
	data->quote = 0;
	data->in_quote = false;
	data->arg = NULL;
	data->expanded_arg = NULL;
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

void	init_redir(t_command *cmd, char	*filename, int append_mode)
{
	t_redir	*redir;
	t_redir	**curr;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		exit(10000);
	redir->filename = ft_strdup(filename);
	redir->append = append_mode;
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
