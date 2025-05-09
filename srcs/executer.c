/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:59:56 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/09 18:31:35 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "cmd.h"
#include "errors.h"
#include "libft.h"
#include "pipes.h"
#include "builtins.h"

static int	parent_process(pid_t pid)
{
	int	status;
	
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

void 	handle_path(char *path, char *cmd, t_data *data)
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

int	execute_single(t_command *cmd, char ***envp, t_data *data)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
		// exit(exit_free(data));
		;
	if (pid == 0)
	{
		if (!cmd || !cmd->args || !cmd->args[0])
			exit(1);
		if (cmd->heredoc_delimiter)
			;
			// setup_heredoc(cmd); // should exit + free pipes in the function if fail
		else if (cmd->input_file)
			open_input(cmd, data);
		if (cmd->output_file)
			open_output(cmd, data);
		path = find_path(cmd->args[0], *envp);
		handle_path(path, cmd->args[0], data);
		execve(path, cmd->args, *envp);
	}
	return (parent_process(pid));
}

void		execute_external(t_command *cmd, t_data *data, int **pipes, int n)
{
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		close_free_pipes(pipes, n); // + exit ?
	if (cmd->heredoc_delimiter)
		;
	// 	setup_heredoc(cmd); // should exit + free pipes in the function if fail
	// else if (cmd->input_file)
	// 	open_input(cmd); // exit + free pipes in this
	// if (cmd->output_file)
	// 	open_output(cmd); // exit + free pipes in this
	path = find_path(cmd->args[0], data->env);
	if (!path)
	{
		g_exit_value = handle_not_found(cmd->args[0], NULL);
		exit(g_exit_value);
	}
	close_free_pipes(pipes, n);
	execve(path, cmd->args, data->env);
	perror(cmd->args[0]);
	free(path);
	exit(1000);
}

void	execute_command(t_command *cmd, char ***envp, int **pipes, t_data *data)
{
	if (is_builtin(cmd->args[0]))
		execute_builtin(cmd, envp, data);
	else
		execute_external(cmd, data, pipes, cmd->number_cmds - 1);
}
