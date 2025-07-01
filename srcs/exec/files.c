/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:15 by lgirerd           #+#    #+#             */
/*   Updated: 2025/07/01 13:18:54 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "colors.h"
#include "files.h"
#include <unistd.h>

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

int	handle_empty_output(t_data *data, t_command *cmd, int *saved_fds)
{
	t_redir	*curr_redir;

	curr_redir = cmd->out_redir;
	while (curr_redir)
	{
		if (curr_redir->filename[0] == '\0')
		{
			ft_putstr_fd(RED"minishell: : No such file or directory\n"RESET, 2);
			return (1);
		}
		open_one_output(curr_redir, data, saved_fds);
		curr_redir = curr_redir->next;
	}
	return (0);
}
