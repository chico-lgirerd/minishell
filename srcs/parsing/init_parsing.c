/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:45:31 by tiaperei          #+#    #+#             */
/*   Updated: 2025/05/16 05:26:30 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "colors.h"
#include "colors.h"
#include "libft.h"

void	init_data(t_data *data, char **env)
{
	data->env = env;
	data->line = NULL;
	data->quote = 0;
	data->expanded_arg = NULL;
	data->args_list = NULL;
	data->first_cmd = NULL;
	data->touched_env = 0;
	data->forks = NULL;
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
