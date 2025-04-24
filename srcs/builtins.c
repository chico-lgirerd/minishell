/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:58:23 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/24 18:17:13 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "minishell.h"
#include "builtins.h"
#include "errors.h"
#include "cmd.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0);
}

void	execute_builtin(t_command *cmd, char ***envp)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		g_exit_value = ft_echo(cmd->args + 1);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		g_exit_value = cd(cmd->args + 1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		g_exit_value = env(*envp);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		g_exit_value = ft_exit(cmd->args + 1);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		g_exit_value = export(cmd->args + 1, envp);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		g_exit_value = pwd();
	else if (ft_strcmp(cmd->args[0], "unset") == 0 && cmd->args[1])
		g_exit_value = unset(cmd->args + 1, envp);
}

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
