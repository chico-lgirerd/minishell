/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:34:07 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/23 17:55:56 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	ft_exit(char **args)
{
	int	exitcode;

	if (!args[0])
		exit(g_exit_value);
	if (args[1])
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	exitcode = ft_atoi(args[0]);
	if (exitcode == 0 && args[0][0] != '0')
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", args[0]);
		exit(2);
	}
	printf("exit\n");
	exit(exitcode % 256);
}
