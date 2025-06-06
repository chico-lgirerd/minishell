/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:59:56 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/06 12:01:39 by tiaperei         ###   ########.fr       */
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
#include "utils.h"

static int	parent_process(t_command *cmd, pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (cmd->heredoc_fd > 2)
		close(cmd->heredoc_fd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
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
		setup_redirection(cmd, data, saved_fds);
		env_arr = env_to_array(data->env);
		if (!env_arr)
			ft_error(data, "allocation failed", errno);
		path = find_path(data, cmd->args[0], env_arr);
		handle_path(path, cmd->args[0], data, env_arr);
		execve(path, cmd->args, env_arr);
		free_chars(env_arr);
		ft_error(data, "execve: An unknown error occured", errno);
	}
	return (parent_process(cmd, pid));
}

void	execute_external(t_command *cmd, t_data *data, t_fork *forks, int n)
{
	char	*path;
	char	**env_arr;

	env_arr = env_to_array(data->env);
	if (!env_arr)
		ft_error(data, "allocation failed", errno);
	path = find_path(data, cmd->args[0], env_arr);
	handle_path(path, cmd->args[0], data, env_arr);
	close_free_pipes(forks->pipes, n);
	execve(path, cmd->args, env_arr);
	free_chars(env_arr);
	free(path);
	ft_error(data, "execve: An unknown error occured", errno);
}

void	execute_command(t_command *cmd, t_fork *forks, t_data *data)
{
	int	saved_fds[2];

	if (is_builtin(cmd->args[0]))
	{
		run_builtins(cmd, data);
		free_all_data(data, true);
	}
	else
	{
		setup_redirection(cmd, data, saved_fds);
		execute_external(cmd, data, forks, cmd->number_cmds - 1);
		if (cmd->heredoc_fd > 2)
			close(cmd->heredoc_fd);
		restore_fds(saved_fds, data);
	}
}
