/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:59:56 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/12 17:03:21 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "errors.h"
#include "cmd.h"
#include "builtins.h"
#include "utils.h"
#include "files.h"
#include "signals.h"

static int	parent_process(t_command *cmd, pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (cmd->heredoc_fd > 2)
		close(cmd->heredoc_fd);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (130);
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
	int returncode;

	manage_signals_in_process();
	pid = fork();
	if (pid == -1)
		return (1);
	setup_process_signals();
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
	signal(SIGINT, SIG_IGN);
	returncode = parent_process(cmd, pid);
	reset_signals();
	return (returncode);
	// return (parent_process(cmd, pid));
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
	int	builtin_code;

	if (is_builtin(cmd->args[0]))
	{
		builtin_code = run_builtins(cmd, data);
		free_all_data(data, true);
		exit(builtin_code);
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

int	handle_heredoc_before_exec(t_data *data)
{
	if (pipe_in_tokens(data->args_list))
		return (0);
	if (proc_heredoc(data, data->first_cmd) == 130)
	{
		data->exit_value = 130;
		free_command(&data->first_cmd);
		free_args_list(&data->args_list);
		free(data->line);
		return (130);
	}
	return (0);
}
