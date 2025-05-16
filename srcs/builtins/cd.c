/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:37:55 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/16 03:08:34 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "colors.h"
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	*get_dirpath(char **args)
{
	char	*dirpath;

	if (!args[0])
	{
		dirpath = getenv("HOME");
		if (!dirpath)
		{
			printf(RED"minishell: cd: HOME not set\n"RESET);
			return (NULL);
		}
	}
	else
		dirpath = args[0];
	while (*dirpath == ' ' || *dirpath == '\t')
		dirpath++;
	if (*dirpath == '\0')
		return (NULL);
	return (dirpath);
}

int	cd(char **args)
{
	char	*dirpath;

	dirpath = get_dirpath(args);
	if (!dirpath)
		return (1);
	if (args[0] && args[1])
	{
		printf(RED"minishell: cd: too many arguments\n"RESET);
		return (1);
	}
	if (chdir(dirpath) != 0)
		return (output_cd_error(errno));
	return (0);
}
