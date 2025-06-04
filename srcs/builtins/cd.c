/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:37:55 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/03 16:24:57 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "colors.h"
#include "builtins.h"
#include "libft.h"
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

int	cd(char **args, t_data *data)
{
	char	*dirpath;
	char	oldpwd[1024];
	char	newpwd[1024];

	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		return (1);
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
	if (update_env_var(data, "OLDPWD", oldpwd))
		exit(EXIT_FAILURE);
	if (getcwd(newpwd, sizeof(newpwd)) == NULL)
		return (1);
	if (update_env_var(data, "PWD", newpwd))
		exit(EXIT_FAILURE);
	return (0);
}
