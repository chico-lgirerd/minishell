/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:21:51 by lgirerd           #+#    #+#             */
/*   Updated: 2025/07/01 14:19:04 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "files.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	open_input(t_command *cmd, t_data *data, int *saved_fds)
{
	int	fd;

	if (!cmd->input_file)
		return (1);
	fd = open(cmd->input_file, O_RDONLY);
	if (fd == -1)
	{
		restore_fds(saved_fds, data);
		exit(output_file_error(errno, cmd->input_file, data));
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		restore_fds(saved_fds, data);
		close(fd);
		exit(dup_error(data, errno));
	}
	close(fd);
	return (1);
}

int	get_flags(t_redir *redir)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (redir->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

int	open_output(t_command *cmd, t_data *data, int *saved_fds)
{
	t_redir	*redir;
	int		fd;
	int		flags;

	redir = cmd->out_redir;
	while (redir)
	{
		flags = get_flags(redir);
		fd = open(redir->filename, flags, 0644);
		if (fd == -1)
		{
			restore_fds(saved_fds, data);
			exit(output_file_error(errno, redir->filename, data));
		}
		if (!redir->next && dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			restore_fds(saved_fds, data);
			exit(dup_error(data, errno));
		}
		close(fd);
		redir = redir->next;
	}
	return (1);
}

void	open_heredoc(t_data *data, t_command *cmd, int *saved_fds)
{
	if (cmd->heredoc_fd > 2)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
		{
			if (cmd->heredoc_fd > 2)
				close(cmd->heredoc_fd);
			exit(dup_error(data, errno));
		}
		close(cmd->heredoc_fd);
	}
	cmd->heredoc_fd = -1;
	close(saved_fds[0]);
	saved_fds[0] = -1;
}

int	open_one_output(t_redir *redir, t_data *data)
{
	int		fd;
	int		flags;

	flags = get_flags(redir);
	fd = open(redir->filename, flags, 0644);
	if (fd == -1)
		return (output_file_error(errno, redir->filename, data));
	close(fd);
	return (1);
}
