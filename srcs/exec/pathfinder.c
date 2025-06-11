/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:13:20 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/11 16:53:45 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cmd.h"
#include "utils.h"
#include <fcntl.h>

static char	*check_paths(t_data *data, char **paths, char *cmd)
{
	int		i;
	char	*part_path;
	char	*path;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/"); // a secure
		if (!part_path)
			ft_error(data, "malloc: failed in check_path", 1);
		path = ft_strjoin(part_path, cmd); // a secure
		if (!path)
			ft_error(data, "malloc: failed in check_path", 1);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			free(path);	
			free_chars(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_chars(paths);
	return (NULL);
}

char	*find_path(t_data *data, char *cmd, char **envp)
{
	char	**paths;
	int		i;

	if (cmd == NULL)
		return (NULL);
	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		if (access(cmd, F_OK) != 0)
			return ("NOFILE");
		else if (access(cmd, X_OK) != 0)
			return ("NOPERM");
	}
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
	{
		free_chars(envp);
		ft_error(data, "split failed", 1);
	}
	return (check_paths(data, paths, cmd));
}
