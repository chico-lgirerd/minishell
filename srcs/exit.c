/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:34:07 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/02 17:26:53 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

#include <errno.h>
#include <string.h>

void	ft_exit(char *code)
{
	int	exitcode;

	exitcode = ft_atoi(code);
	if (exitcode == 0 && code[0] != '0')
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", code);
		exit(2);
	}
	printf("exit\n");
	exit(exitcode);
}
