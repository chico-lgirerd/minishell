/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:15 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/08 15:54:28 by lgirerd          ###   ########lyon.fr   */
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

int	open_input(t_command *cmd)
{
	int	fd;

	if (!cmd->input_file)
		return (1);
	fd = open(cmd->input_file, O_RDONLY);
	if (fd == -1)
		return (output_error(errno));
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
