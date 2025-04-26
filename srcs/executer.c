/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:59:56 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/26 17:53:30 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "cmd.h"
#include "errors.h"
#include "libft.h"
#include "pipes.h"
#include "builtins.h"

void	child_process(t_command *cmd, char *path, char ***envp)
{
	if (open_input(cmd) != 1 || open_output(cmd) != 1)
	{
		free(path);
		exit(10000);
	}
	execve(path, cmd->args, *envp);
	ft_putstr_fd("minishell: ", 2);
	perror(cmd->args[0]);
	free(path);
	exit(1000);
}

void	parent_process(pid_t pid)
{
	int	status;
	
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_value = WEXITSTATUS(status);
}

// void	execute_external(t_command *cmd, char ***envp)
// {
// 	char	*path;
// 	pid_t	pid;

// 	path = find_path(cmd->args[0], *envp);
// 	if (!path)
// 	{
// 		g_exit_value = handle_not_found(cmd->args[0]);
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 		child_process(cmd, path, envp);
// 	else if (pid < 0)
// 		perror("minishell: fork");
// 	else
// 		parent_process(pid);
// 	free(path);
// }

int	execute_single(t_command *cmd, char ***envp)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
		exit(10000);
	if (pid == 0)
	{
		if (!cmd || !cmd->args || !cmd->args[0])
			exit(1);
		if (cmd->heredoc_delimiter)
			;
			// setup_heredoc(cmd); // should exit + free pipes in the function if fail
		else if (cmd->input_file)
			open_input(cmd); // exit + free pipes in this
		if (cmd->output_file)
			open_output(cmd); // exit + free pipes in this
		path = find_path(cmd->args[0], *envp);
		execve(path, cmd->args, *envp);
	}
	parent_process(pid);
	return (1);
}

void		execute_external(t_command *cmd, char ***envp, int **pipes, int n)
{
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		close_free_pipes(pipes, n); // + exit ?
	if (cmd->heredoc_delimiter)
		;
		// setup_heredoc(cmd); // should exit + free pipes in the function if fail
	else if (cmd->input_file)
		open_input(cmd); // exit + free pipes in this
	if (cmd->output_file)
		open_output(cmd); // exit + free pipes in this
	path = find_path(cmd->args[0], *envp);
	if (!path)
	{
		g_exit_value = handle_not_found(cmd->args[0]);
		exit(g_exit_value);
	}
	close_free_pipes(pipes, n);
	execve(path, cmd->args, *envp);
	perror(cmd->args[0]);
	free(path);
	exit(1000);
}

void	execute_command(t_command *cmd, char ***envp, int **pipes, int n)
{
	if (is_builtin(cmd->args[0]))
		// execute_builtin(cmd, envp);
		;
	else
		execute_external(cmd, envp, pipes, n);
}
