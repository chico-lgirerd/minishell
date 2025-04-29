/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:37:55 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/29 16:16:18 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <dirent.h>
#include <unistd.h>
#include "stdio.h"

int	cd(char **args)
{
	DIR		*dir;
	char	*dirpath;

	if (!args[0])
		return (1);
	if (args[1])
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	dirpath = args[0];
	while (*dirpath == ' ' || *dirpath == '\t')
		dirpath++;
	if (*dirpath == '\0')
		return (output_error(ENOENT));
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
