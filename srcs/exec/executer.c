/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:59:56 by lgirerd           #+#    #+#             */
/*   Updated: 2025/07/17 13:53:00 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "cmd.h"
#include "builtins.h"
#include "utils.h"
#include "files.h"
#include "signals.h"
#include "parsing.h"
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

int	finish_executing(int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (130);
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		return (131);
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGPIPE)
	{
		write(STDOUT_FILENO, "SIGPIPE happened\n", 17);
		return (141);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static int	parent_process(t_command *cmd, pid_t pid)
{
	int					status;

	status = 0;
	waitpid(pid, &status, 0);
	if (cmd->heredoc_fd > 2)
		close(cmd->heredoc_fd);
	return (finish_executing(status));
}

int	execute_single(t_command *cmd, t_data *data)
{
	pid_t	pid;
	char	*path;
	int		saved_fds[2];
	char	**env_arr;

	handle_signal_wait();
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		handle_signal_child();
		setup_redirection(cmd, data, saved_fds);
		env_arr = env_to_array(data->env);
		if (!env_arr)
			ft_error(data, "allocation failed", errno);
		path = find_path(data, cmd->args[0], env_arr);
		ft_close_arr(saved_fds);
		command_in_dir(&path, cmd);
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
	command_in_dir(&path, cmd);
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
	int	builtin_code;

	if (is_builtin(cmd))
	{
		builtin_code = run_builtins(cmd, data);
		free_all_data(data, true);
		exit(builtin_code);
	}
	else
	{
		if (!cmd->args || !cmd->args[0])
		{
			free_all_data(data, true);
			exit(0);
		}
		setup_redirection(cmd, data, saved_fds);
		execute_external(cmd, data, forks, cmd->number_cmds - 1);
		if (cmd->heredoc_fd > 2)
			close(cmd->heredoc_fd);
		restore_fds(saved_fds, data);
	}
}
