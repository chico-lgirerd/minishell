/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:59:56 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/17 18:10:21 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "cmd.h"
#include "errors.h"
#include "libft.h"
#include "pipes.h"
#include "builtins.h"
#include "files.h"
#include "colors.h"

static int	parent_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

void	handle_path(char *path, char *cmd, t_data *data)
{
	if (!path)
		exit(handle_not_found(cmd, data));
	if (ft_strcmp(cmd, ".") == 0)
	{
		free(path);
		exit(handle_point(data));
	}
	else if (ft_strcmp(cmd, "..") == 0)
	{
		free(path);
		exit(handle_not_found(cmd, data));
	}
	else if (ft_strcmp(path, "NOPERM") == 0)
	{
		free(path);
		exit(handle_noperm(cmd, data));
	}
	else if (ft_strcmp(path, "NOFILE") == 0)
	{
		free(path);
		exit(handle_nofile(cmd, data));
	}
}

int	execute_single(t_command *cmd, t_data *data)
{
	pid_t	pid;
	char	*path;
	int		saved_fds[2];
	char	**env_arr;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (!cmd || !cmd->args || !cmd->args[0])
		{
			free_all_data(data);
			exit(EXIT_FAILURE);
		}
		setup_redirection(cmd, data, saved_fds);
		env_arr = env_to_array(data->env);
		if (!env_arr)
			exit(1);
		path = find_path(cmd->args[0], env_arr);
		handle_path(path, cmd->args[0], data);
		execve(path, cmd->args, env_arr);
		free_chars(env_arr);
		exit (1);
	}
	return (parent_process(pid));
}

void	execute_external(t_command *cmd, t_data *data, t_fork *forks, int n)
{
	char	*path;
	char	**env_arr;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		free_all_data(data);
		exit(EXIT_FAILURE);
	}
	env_arr = env_to_array(data->env);
	if (!env_arr)
		exit(1);
	path = find_path(cmd->args[0], env_arr);
	if (!path)
		exit(handle_not_found(cmd->args[0], data));
	close_free_pipes(forks->pipes, n);
	execve(path, cmd->args, env_arr);
	free_chars(env_arr);
	ft_putstr_fd(RED"minishell: execve: An unknown error occured\n"RESET, 2);
	free(path);
	free_all_data(data);
	exit(1);
}

void	execute_command(t_command *cmd, t_fork *forks, t_data *data)
{
	int	saved_fds[2];

	if (is_builtin(cmd->args[0]))
	{
		run_builtins(cmd, data);
		free_all_data(data);
	}
	else
	{
		setup_redirection(cmd, data, saved_fds);
		execute_external(cmd, data, forks, cmd->number_cmds - 1);
		restore_fds(saved_fds, data);
	}
}
