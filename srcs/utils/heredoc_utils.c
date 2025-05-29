/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:40:06 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/19 23:10:10 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "errors.h"

void	add_heredoc(t_command *cmd, char *delim)
{
	t_heredoc	*new;
	t_heredoc	*last;

	new = malloc(sizeof(t_heredoc));
	if (!new)
		exit(ENOMEM); // ou return ?
	ft_memset(new, 0, sizeof(t_heredoc));
	new->delim = ft_strdup(delim);
	if (!new->delim)
		exit(1);
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
