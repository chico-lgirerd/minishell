/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:52:52 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/24 17:01:54 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "cmd.h"
#include "libft.h"
#include <stdio.h>

int	handle_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (CMD_NOT_FOUND);
}

int	output_error(int errcode)
{
	const char	*red;
	const char	*reset;

	reset = "\033[0m";
	red = "\033[31m";
	write(2, red, 5);
	write(2, strerror(errcode), ft_strlen(strerror(errcode)));
	write(2, "\n", 2);
	write(2, reset, 4);
	// perror("Failed to open directory");
	return (errcode);
}
