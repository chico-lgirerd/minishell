/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:59:56 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/03 16:14:48 by lgirerd          ###   ########lyon.fr   */
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

static int	parent_process(t_command *cmd, pid_t pid)
{
	int	status;

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
		//if (!cmd || !cmd->args || !cmd->args[0])
			//exit(handle_empty_cmd(data, cmd));
		setup_redirection(cmd, data, saved_fds);
		env_arr = env_to_array(data->env);
		if (!env_arr)
			exit(ENOMEM);
		path = find_path(cmd->args[0], env_arr);
		handle_path(path, cmd->args[0], data, env_arr);
		execve(path, cmd->args, env_arr);
		free_chars(env_arr);
		exit(EXIT_FAILURE);
	}
	return (parent_process(cmd, pid));
}

void	execute_external(t_command *cmd, t_data *data, t_fork *forks, int n)
{
	char	*path;
	char	**env_arr;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		free_all_data(data, false);
		exit(EXIT_FAILURE);
	}
	env_arr = env_to_array(data->env);
	if (!env_arr)
		exit(ENOMEM);
	path = find_path(cmd->args[0], env_arr);
	handle_path(path, cmd->args[0], data, env_arr);
	close_free_pipes(forks->pipes, n);
	execve(path, cmd->args, env_arr);
	free_chars(env_arr);
	ft_putstr_fd(RED"minishell: execve: An unknown error occured\n"RESET, 2);
	free(path);
	free_all_data(data, false);
	exit(EXIT_FAILURE);
}

void	execute_command(t_command *cmd, t_fork *forks, t_data *data)
{
	int	saved_fds[2];

	if (is_builtin(cmd->args[0]))
	{
		run_builtins(cmd, data);
		free_all_data(data, false);
	}
	else
	{
		setup_redirection(cmd, data, saved_fds);
		execute_external(cmd, data, forks, cmd->number_cmds - 1);
		restore_fds(saved_fds, data);
	}
}
