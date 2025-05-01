/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:52:52 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/01 13:59:11 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "cmd.h"
#include "libft.h"
#include "colors.h"
#include <stdio.h>

int	handle_not_found(char *cmd)
{
	ft_putstr_fd(RED"minishell: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n"RESET, 2);
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
