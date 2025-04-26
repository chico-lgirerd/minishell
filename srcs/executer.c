/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:59:56 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/26 12:01:30 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "cmd.h"

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

void	execute_external(t_command *cmd, char ***envp)
{
	char	*path;
	pid_t	pid;

	path = find_path(cmd->args[0], *envp);
	if (!path)
	{
		g_exit_value = handle_not_found(cmd->args[0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
		child_process(cmd, path, envp);
	else if (pid < 0)
		perror("minishell: fork");
	else
		parent_process(pid);
	free(path);
}

void	execute_command(t_command *cmd, char ***envp)
{		
		if (is_builtin(cmd->args[0]))
		execute_builtin(cmd, envp);
	else
		execute_external(cmd, envp);
}
