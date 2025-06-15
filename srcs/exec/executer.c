/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:59:56 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/15 17:07:46 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "errors.h"
#include "cmd.h"
#include "builtins.h"
#include "utils.h"
#include "files.h"
#include "signals.h"
#include "minishell.h"

static int	parent_process(t_command *cmd, pid_t pid)
{
	int	status;
	struct sigaction original;
	struct sigaction ignore;
	
	setup_signals_parent(&original, &ignore);
	status = 0;
	waitpid(pid, &status, 0);
	if (cmd->heredoc_fd > 2)
		close(cmd->heredoc_fd);
	// if (g_signal == 2)
		// return (130);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		sigaction(SIGINT, &original, NULL);
		return (130);
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		sigaction(SIGINT, &original, NULL);
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);	
		return (131);
	}
	if (WIFEXITED(status))
	{
		sigaction(SIGINT, &original, NULL);
		return (WEXITSTATUS(status));
	}
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
		manage_signals_in_process();
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
	g_signal = 0;
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
