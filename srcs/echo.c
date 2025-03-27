/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:56:01 by lgirerd           #+#    #+#             */
/*   Updated: 2025/03/27 18:45:28 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"
#include "libft.h"

void	echo_n(int argc, char **args, char **env)
{
	int	i;

	i = 2;
	(void)env; // a gerer
	while (args[i])
	{
		printf("%s", args[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
}

void	echo(int argc, char **args, char **env)
{
	int	i;

	i = 1;
	(void)env; //a gerer
	while (args[i])
	{
		printf("%s", args[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	ft_echo(char **args, char **env)
{
	int argc;

	argc = 0;
	while(args)
		argc++;
	if (ft_strcmp("-n", args[1]) == 0)
		echo_n(argc, args, env);
	else
		echo(argc, args, env);	
}
