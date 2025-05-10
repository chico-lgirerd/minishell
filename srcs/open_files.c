/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:15 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/10 19:07:13 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "parsing.h"
#include "libft.h"
#include "colors.h"
#include <fcntl.h>

int	output_file_error(int errcode, char *filename, t_data *data)
{
	if (errcode == EACCES)
	{
		ft_putstr_fd(RED"minishell: "RESET, 2);
		if (filename)
			ft_putstr_fd(filename, 2);
		ft_putstr_fd(RED": Permission denied\n"RESET, 2);
	}
	else if (errcode == EISDIR)
	{
		ft_putstr_fd(RED"minishell: "RESET, 2);
		if (filename)
			ft_putstr_fd(filename, 2);
		ft_putstr_fd(RED": Is a directory\n"RESET, 2);
	}
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
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	open_output(t_command *cmd, t_data *data)
{
	int	fd;
	int	flags;

	if (!cmd->output_file)
		return (1);
	flags = O_WRONLY | O_CREAT;
	if (cmd->append_output)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->output_file, flags, 0644);
	if (fd == -1)
		exit(output_file_error(errno, cmd->output_file, data));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

void	setup_redirection(t_command *cmd, t_data *data, int *saved_fds)
{
	saved_fds[0] = -1;
	saved_fds[1] = -1;
	if (cmd->input_file)
	{
		saved_fds[0] = dup(STDIN_FILENO);
		if (saved_fds[0] == -1)
			exit(10000);
		open_input(cmd, data);
	}
	if (cmd->output_file)
	{
		saved_fds[1] = dup(STDOUT_FILENO);
		if (saved_fds[1] == -1)
			exit(10000);
		open_output(cmd, data);
	}
}

void	restore_fds(int *saved_fds)
{
	if (saved_fds[0] != -1)
	{
		dup2(saved_fds[0], STDIN_FILENO);
		close(saved_fds[0]);
	}
	if (saved_fds[1] != -1)
	{
		dup2(saved_fds[1], STDOUT_FILENO);
		close(saved_fds[1]);
	}
}

