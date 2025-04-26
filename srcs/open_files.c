/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:15 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/26 14:52:22 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "parsing.h"
#include <fcntl.h>

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

int	open_output(t_command *cmd)
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
		return (output_error(errno));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}
