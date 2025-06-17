/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:40:06 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/17 18:50:07 by lgirerd          ###   ########lyon.fr   */
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

void	input_to_fd(t_data *data, char *buff, int fd, char *delim)
{
	t_args	*current;
	bool	in_quote;

	current = data->args_list;
	while (current)
	{
		if (current->content && ft_strcmp(current->content, delim) == 0)
			in_quote = current->in_quote;
		current = current->next;
	}
	if (!in_quote)
	{
		expand_arg(data, buff);
		ft_putendl_fd(data->expanded_arg, fd);
	}
	else
		ft_putendl_fd(buff, fd);
}

int	handle_heredoc_before_exec(t_data *data)
{
	if (pipe_in_tokens(data->args_list))
		return (0);
	if (proc_heredoc(data, data->first_cmd) == 130)
	{
		data->exit_value = 130;
		free_command(&data->first_cmd);
		free_args_list(&data->args_list);
		free(data->line);
		return (130);
	}
	return (0);
}
