/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:13:20 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/06 10:13:51 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cmd.h"
#include <fcntl.h>

char	*check_paths(char **paths, char *cmd)
{
	int		i;
	char	*part_path;
	char	*path;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_chars(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_chars(paths);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	int		i;

	if (cmd == NULL)
		return (NULL);
	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		if (access(cmd, F_OK) != 0)
			return (ft_strdup("NOFILE"));
		else if (access(cmd, X_OK) != 0)
			return (ft_strdup("NOPERM"));
	}
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	return (check_paths(paths, cmd));
}
