/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:37:55 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/20 19:37:03 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "errors.h"
#include "colors.h"
#include "builtins.h"
#include "libft.h"
#include <unistd.h>

char	*get_dirpath(t_data *data, char **args)
{
	char	*dirpath;

	if (!args[0])
	{
		dirpath = get_env_value("HOME", data->env);
		if (!dirpath)
		{
			ft_putendl_fd(RED"minishell: cd: HOME not set"RESET, 2);
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
	dirpath = get_dirpath(data, args);
	if (!dirpath)
		return (1);
	if (args[0] && args[1])
	{
		ft_putendl_fd(RED"minishell: cd: too many arguments"RESET, 2);
		return (1);
	}
	if (chdir(dirpath) != 0)
		return (output_cd_error(errno));
	if (update_env_var(data, "OLDPWD", oldpwd))
		return (1);
	if (getcwd(newpwd, sizeof(newpwd)) == NULL)
		return (1);
	if (update_env_var(data, "PWD", newpwd))
		return (1);
	return (0);
}
