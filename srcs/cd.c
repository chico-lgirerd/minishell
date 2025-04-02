/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:37:55 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/02 17:27:13 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <dirent.h>
#include <unistd.h>

void	cd(char *dirname)
{
	DIR	*dir;

	while ((*dirname) && (*dirname == ' ' || *dirname == '\t'))
		dirname++;
	if (*dirname == '\0')
		return ;
	dir = opendir(dirname);
	if (dir != NULL)
	{
		closedir(dir);
		if (chdir(dirname) != 0)
			output_error(errno);
	}
	else
		output_error(errno);
}
