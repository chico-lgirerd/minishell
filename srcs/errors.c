/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:52:52 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/07 15:59:45 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "cmd.h"
#include "libft.h"
#include "colors.h"
#include <stdio.h>

int	handle_not_found(char *cmd, t_command *first_cmd)
{
	ft_putstr_fd(RED"minishell: "RESET, 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(RED": command not found\n"RESET, 2);
	if (first_cmd)
		free_command(&first_cmd);
	return (CMD_NOT_FOUND);
}

int	handle_noperm(char *cmd, t_command *first_cmd)
{
	ft_putstr_fd(RED"minishell: "RESET, 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(RED": Permission denied\n"RESET, 2);
	free_command(&first_cmd);
	return (126);
}

int	handle_nofile(char *cmd, t_command *first_cmd)
{
	ft_putstr_fd(RED"minishell: "RESET, 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(RED": No such file or directory\n"RESET, 2);
	free_command(&first_cmd);
	return (CMD_NOT_FOUND);
}

int	output_error(int errcode)
{
	if (errcode == ENOTDIR)
		printf(RED"minishell: cd: Not a directory\n"RESET);
	else if (errcode == EACCES)
		printf(RED"minishell: cd: Permission denied\n"RESET);
	else if (errcode == ENOENT)
		printf(RED"minishell: cd: No such file or directory\n"RESET);
	else
		printf(RED"minishell: An unknown error occured\n"RESET);
	return (1);
}
