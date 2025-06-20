/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:56:01 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/20 19:31:03 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

int	valid_newline_flag(char *flag)
{
	int	i;

	i = 1;
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args, t_command *cmd)
{
	int	newline;
	int	i;
	int	first_arg;

	newline = 1;
	i = -1;
	first_arg = 1;
	while (args[++i] && ((args[i][0] == '-' && args[i][1] != '\0')
		&& valid_newline_flag(args[i] + 1)))
		newline = 0;
	while (args && i < cmd->count_args)
	{
		if (!first_arg && args[i] && args[i - 1])
			printf(" ");
		if (args[i])
			printf("%s", args[i]);
		first_arg = 0;
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
