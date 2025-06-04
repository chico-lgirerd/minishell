/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:40:06 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/04 17:30:12 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "errors.h"
#include "utils.h"

void	add_heredoc(t_data *data, t_command *cmd, char *delim)
{
	t_heredoc	*new;
	t_heredoc	*last;

	(void)delim;
	new = malloc(sizeof(t_heredoc));
	if (!new)
		ft_error(data, "malloc: failed add_heredoc");
	ft_memset(new, 0, sizeof(t_heredoc));
	new->delim = ft_strdup(delim);
	if (!new->delim)
	{
		free(new);
		ft_error(data, "malloc: failed add_heredoc");
	}
	if (!cmd->heredocs)
		cmd->heredocs = new;
	else
	{
		last = cmd->heredocs;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	free_heredocs(t_command *cmd)
{
	t_heredoc	*curr;

	while (cmd->heredocs)
	{
		curr = cmd->heredocs;
		free(curr->tempfile);
		free(curr->delim);
		cmd->heredocs = cmd->heredocs->next;
		free(curr);
	}
}

