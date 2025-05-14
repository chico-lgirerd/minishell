/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:56:01 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/14 11:47:02 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <stdlib.h>

int	ft_echo(char **args)
{
	int	newline;
	int	i;
	int	first_arg;

	newline = 1;
	i = 0;
	first_arg = 1;
	while (args && args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args && args[i])
	{
		if (args[i][0] != '\0')
		{
			if (!first_arg)
				printf(" ");
			printf("%s", args[i]);
			// if (args[i + 1])
				// printf(" ");
			first_arg = 0;
		}
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
