/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:37:55 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/23 18:02:26 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <dirent.h>
#include <unistd.h>

int	cd(char **args)
{
	DIR		*dir;
	char	*dirpath;

	if (!args[0] || args[1])
		return (1);
	dirpath = args[0];
	while ((*dirpath) && (*dirpath == ' ' || *dirpath == '\t'))
		dirpath++;
	if (*dirpath == '\0')
		return (output_error(EINVAL));
	dir = opendir(dirpath);
	if (dir != NULL)
	{
		closedir(dir);
		if (chdir(dirpath) != 0)
			return (output_error(errno));
		else
			return (0);
	}
	else
		return (output_error(errno));
}
