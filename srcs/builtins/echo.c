/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:56:01 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/07 19:48:45 by tiaperei         ###   ########.fr       */
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
		if (!first_arg)
			printf(" ");
		printf("%s", args[i]);
		first_arg = 0;
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
