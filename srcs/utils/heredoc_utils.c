/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:40:06 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/21 16:59:54 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "utils.h"
#include "colors.h"
#include "files.h"

void	add_heredoc(t_data *data, t_command *cmd, char *delim)
{
	t_heredoc	*new;
	t_heredoc	*last;

	(void)delim;
	new = malloc(sizeof(t_heredoc));
	if (!new)
		ft_error(data, "malloc: failed add_heredoc", errno);
	ft_memset(new, 0, sizeof(t_heredoc));
	new->delim = ft_strdup(delim);
	if (!new->delim)
	{
		free(new);
		ft_error(data, "malloc: failed add_heredoc", errno);
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

void	print_eof_warning(char *delim)
{
	ft_putstr_fd(RED"warning: here-doc document delimited by", 2);
	ft_putstr_fd(" end-of-file (wanted '", 2);
	ft_putstr_fd(delim, 2);
	ft_putendl_fd("')"RESET, 2);
}
