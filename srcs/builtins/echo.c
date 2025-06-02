/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:56:01 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/02 15:39:36 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <stdlib.h>

int	ft_echo(char **args, t_command *cmd)
{
	int	newline;
	int	i;
	int	first_arg;

	newline = 1;
	i = 0;
	first_arg = 1;
	while (args && args[i] && (ft_strcmp(args[i], "-n") == 0))
	{
		newline = 0;
		i++;
	}
	while (ft_strcmp(args[i], "-") == 0)
		i++;
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
