/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:17:09 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/19 15:39:55 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "colors.h"
#include "libft.h"
#include "minishell.h"
#include "cmd.h"
#include "errors.h"
#include <sys/stat.h>

int	handle_empty_cmd(t_data *data, t_command *cmd)
{
	int	saved_fds[2];

	setup_redirection(cmd, data, saved_fds);
	restore_fds(saved_fds, data);
	return (0);
}

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		ft_putendl_fd(RED"minishell: stat failed"RESET, 2);
		return (-1);
	}
	return (S_ISDIR(path_stat.st_mode));
}

int	handle_isdir(char *cmd, t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putendl_fd(RED": Is a directory"RESET, 2);
	free_all_data(data);
	return (126);
}

void	handle_other_path(char *path, char *cmd, t_data *data, char **env)
{
	if (ft_strcmp(path, "NOFILE") == 0)
	{
		free(path);
		free_chars(env);
		exit(handle_nofile(cmd, data));
	}
	else if (is_directory(path))
	{
		free(path);
		free_chars(env);
		exit(handle_isdir(cmd, data));
	}
}

