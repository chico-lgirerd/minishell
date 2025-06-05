/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:15 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/05 16:00:41 by lgirerd          ###   ########lyon.fr   */
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
	free_all_data(data, true);
	return (1);
}

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
	if (cmd->heredoc_fd >= 0)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
		{
			printf("Dup2 error in heredoc_fd : %d\n", cmd->heredoc_fd);
			exit(dup_error(data, errno)); // peut etre close hrdc fd / sav fd 0
		}
		close(cmd->heredoc_fd);
	}
	cmd->heredoc_fd = -1;
	close(saved_fds[0]);
	saved_fds[0] = -1;
}

int	save_fd(t_data *data, int fd)
{
	int	dup_fd;
	
	dup_fd = dup(fd);
	if (dup_fd == -1)
		exit(dup_error(data, errno));
	return (dup_fd);
}

void	setup_redirection(t_command *cmd, t_data *data, int *saved_fds)
{
	saved_fds[0] = -1;
	saved_fds[1] = -1;
	if (cmd->out_redir)
	{
		saved_fds[1] = save_fd(data, STDOUT_FILENO);
		open_output(cmd, data, saved_fds);
	}
	if (cmd->heredocs && cmd->heredoc_fd != -1)
	{
		saved_fds[0] = save_fd(data, STDIN_FILENO);
		open_heredoc(data, cmd, saved_fds);
	}
	else if (cmd->input_file && cmd->heredoc_fd == -2)
	{
		saved_fds[0] = save_fd(data, STDIN_FILENO);
		open_input(cmd, data, saved_fds);
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
