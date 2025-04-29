/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:37:55 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/29 18:11:31 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "colors.h"
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

char	*get_dirpath(char **args)
{
	char	*dirpath;
	
	if (!args[0])
	{
		dirpath = getenv("HOME");
		if (!dirpath)
		{
			printf(RED"minishell: cd: HOME not set\n"RESET);
			return (1);
		}
	}
	else
		dirpath = args[0];
	while (*dirpath == ' ' || *dirpath == '\t')
		dirpath++;
	if (*dirpath == '\0')
		return (output_error(ENOENT));
	return (dirpath)
}

int	cd(char **args)
{
	DIR		*dir;
	char	*dirpath;
	
	if (args[1])
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	dirpath = get_dirpath(args);
	if (!dirpath)
		return (1);
	dir = opendir(dirpath);
	if (dir)
	{
		closedir(dir);
		if (chdir(dirpath) != 0)
			return (output_error(errno));
		return (0);
	}
	return (output_error(errno));
}
