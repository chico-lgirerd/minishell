/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:52:52 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/14 17:03:55 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "cmd.h"
#include "libft.h"
#include "colors.h"
#include <stdio.h>

int	handle_not_found(char *cmd, t_data *data, t_fork *forks)
{
	ft_putstr_fd(RED"minishell: "RESET, 2);
	if (cmd && cmd[0] != '\0')
		ft_putstr_fd(cmd, 2);
	else
		ft_putstr_fd("", 2);
	ft_putstr_fd(RED": command not found\n"RESET, 2);
	free_all_data(data);
	if (forks)
	{
		if (forks->pids)
			free(forks->pids);
		if (forks->pipes)
			close_free_pipes(forks->pipes, forks->num_cmds - 1);
	}
	return (CMD_NOT_FOUND);
}

int	handle_noperm(char *cmd, t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(RED": Permission denied\n"RESET, 2);
	free_all_data(data);
	return (126);
}

int	handle_nofile(char *cmd, t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(RED": No such file or directory\n"RESET, 2);
	free_all_data(data);
	return (CMD_NOT_FOUND);
}

int	handle_point(t_data *data)
{
	ft_putstr_fd(RED"minishell: .: filename argument required\n.:", 2);
	ft_putstr_fd("usage: . filename [arguments]\n"RESET, 2);
	free_all_data(data);
	return (2);
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
