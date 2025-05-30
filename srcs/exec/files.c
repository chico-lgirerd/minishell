/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:15 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/30 17:10:17 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "parsing.h"
#include "libft.h"
#include "colors.h"
#include "files.h"
#include <fcntl.h>

int	output_file_error(int errcode, char *filename, t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, 2);
	if (filename)
		ft_putstr_fd(filename, 2);
	if (errcode == EACCES)
		ft_putstr_fd(RED": Permission denied\n"RESET, 2);
	else if (errcode == EISDIR)
		ft_putstr_fd(RED": Is a directory\n"RESET, 2);
	else if (errcode == ENOENT)
		ft_putstr_fd(RED": No such file or directory\n"RESET, 2);
	else
		ft_putstr_fd(RED": An unknown error occured\n"RESET, 2);
	free_all_data(data);
	return (1);
}

int	open_input(t_command *cmd, t_data *data)
{
	int	fd;

	if (!cmd->input_file)
		return (1);
	fd = open(cmd->input_file, O_RDONLY);
	if (fd == -1)
		exit(output_file_error(errno, cmd->input_file, data));
	if (dup2(fd, STDIN_FILENO) != 0)
		exit(dup_error(data, errno));
	close(fd);
	return (1);
}

int	open_output(t_command *cmd, t_data *data)
{
	t_redir	*redir;
	int		fd;
	int		flags;

	redir = cmd->out_redir;
	while (redir)
	{
		flags = O_WRONLY | O_CREAT;
		if (redir->append)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(redir->filename, flags, 0644);
		if (fd == -1)
			exit(output_file_error(errno, redir->filename, data));
		if (!redir->next && dup2(fd, STDOUT_FILENO) != 0)
			exit(dup_error(data, errno));
		close(fd);
		redir = redir->next;
	}
	return (1);
}

void	setup_redirection(t_command *cmd, t_data *data, int *saved_fds)
{
	saved_fds[0] = -1;
	saved_fds[1] = -1;
	if (cmd->out_redir)
	{
		saved_fds[1] = dup(STDOUT_FILENO);
		if (saved_fds[1] == -1)
			exit(dup_error(data, errno));
		open_output(cmd, data);
	}
	if (cmd->heredocs)
	{
		saved_fds[0] = dup(STDIN_FILENO);
		if (saved_fds[0] == -1)
			exit(dup_error(data, errno));
		proc_heredoc(data, cmd);
		dup2(cmd->heredoc_fd, STDIN_FILENO); // a secure
		close(cmd->heredoc_fd);
		close(saved_fds[0]);
		saved_fds[0] = -1;
	}
	else if (cmd->input_file && cmd->heredoc_fd == -2)
	{
		saved_fds[0] = dup(STDIN_FILENO);
		if (saved_fds[0] == -1)
			exit(dup_error(data, errno));
		open_input(cmd, data);
	}
}

void	restore_fds(int *saved_fds, t_data *data)
{
	if (saved_fds[0] != -1)
	{
		dup2(saved_fds[0], STDIN_FILENO);
		if (saved_fds[0] == -1)
			exit(dup_error(data, errno));
		close(saved_fds[0]);
	}
	if (saved_fds[1] != -1)
	{
		dup2(saved_fds[1], STDOUT_FILENO);
		if (saved_fds[1] == -1)
			exit(dup_error(data, errno));
		close(saved_fds[1]);
	}
}
