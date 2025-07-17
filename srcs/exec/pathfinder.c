/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:13:20 by lgirerd           #+#    #+#             */
/*   Updated: 2025/07/17 11:46:03 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "cmd.h"
#include "utils.h"
#include "builtins.h"
#include <fcntl.h>
#include <unistd.h>

static char	*check_paths(t_data *data, char **paths, char *cmd)
{
	int		i;
	char	*part_path;
	char	*path;

	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		if (!part_path)
			ft_error(data, "malloc: failed in check_path", 1);
		path = ft_strjoin(part_path, cmd);
		if (!path)
			ft_error(data, "malloc: failed in check_path", 1);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			if (!ft_strcmp(path, "/usr/local/sbin/"))
				free(path);
			free_chars(paths);
			return (path);
		}
		free(path);
	}
	free_chars(paths);
	return (NULL);
}

char	*handle_file_path(char *cmd)
{
	if (access(cmd, F_OK) != 0)
		return ("NOFILE");
	else if (access(cmd, X_OK) != 0)
		return ("NOPERM");
	return (cmd);
}

char	*find_path(t_data *data, char *cmd, char **envp)
{
	char	**paths;
	int		i;

	if (cmd == NULL)
		return (NULL);
	if (ft_strncmp(cmd, "./", 2) == 0)
		return (handle_file_path(cmd));
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

void	command_in_dir(char **path, t_command *cmd)
{
	if (!*path && !is_builtin(cmd))
		*path = handle_file_path(ft_strjoin("./", cmd->args[0]));
}
