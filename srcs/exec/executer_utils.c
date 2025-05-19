/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:17:09 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/19 23:36:42 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "colors.h"
#include "libft.h"
#include "minishell.h"
#include "cmd.h"
#include "errors.h"
#include <sys/stat.h>

int	handle_empty_cmd(t_data *data, t_command *cmd, char **env)
{
	int	saved_fds[2];

	printf("11111111111\n");
	
	if (cmd->args && !cmd->args[0][0])
		return (127);
	if (cmd->input_file && access(cmd->input_file, F_OK) == 0)
		return (0);
	if (cmd->input_file && !cmd->out_redir)
	{
		printf("222222222\n");		
		handle_nofile(cmd->input_file, data);
		init_data(data, env);
		return (1);
	}
	setup_redirection(cmd, data, saved_fds);
	restore_fds(saved_fds, data);
	printf("333333333\n");
	return (0);
}

void	handle_path(char *path, char *cmd, t_data *data, char **env_arr)
{
	if (!path)
	{
		free_chars(env_arr);
		exit(handle_not_found(cmd, data));
	}
	if (ft_strcmp(cmd, ".") == 0)
	{
		free(path);
		free_chars(env_arr);
		exit(handle_point(data));
	}
	else if (ft_strcmp(cmd, "..") == 0)
	{
		free(path);
		free_chars(env_arr);
		exit(handle_not_found(cmd, data));
	}
	else if (ft_strcmp(path, "NOPERM") == 0)
	{
		free(path);
		free_chars(env_arr);
		exit(handle_noperm(cmd, data));
	}
	handle_other_path(path, cmd, data, env_arr);
}

void	handle_other_path(char *path, char *cmd, t_data *data, char **env_arr)
{
	if (ft_strcmp(path, "NOFILE") == 0)
	{
		free(path);
		free_chars(env_arr);
		exit(handle_nofile(cmd, data));
	}
	else if (is_directory(path))
	{
		free(path);
		free_chars(env_arr);
		exit(handle_isdir(cmd, data));
	}
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
