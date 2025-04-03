/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:56:01 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/03 12:56:38 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	echo_n(char *args, char **env)
{
	(void)env;
	printf("%s", args);
}

void	echo(char *args, char **env)
{
	int	i;

	i = 1;
	(void)env; //a gerer
	printf("%s\n", args);
}

void	ft_echo(char *args, char **env)
{
	if (ft_strncmp("echo -n ", args, 8) == 0)
		echo_n(args + 8, env);
	else
		echo(args + 5, env);
}
