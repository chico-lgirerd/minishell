/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:13:20 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/08 14:24:08 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cmd.h"
#include "builtins.h"
#include <fcntl.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

char	*check_paths(char **paths, char *cmd)
{
	int		i;
	char	*part_path;
	char	*path;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_chars(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_chars(paths);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	int		i;

	if (cmd == NULL)
		return (NULL);
	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		if (access(cmd, F_OK) != 0)
			return (ft_strdup("NOFILE"));
		else if (access(cmd, X_OK) != 0)
			return (ft_strdup("NOPERM"));
	}
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	return (check_paths(paths, cmd));
}

void	execute(char *avc, char **envp)
{
	char	**cmd;
	char	*path;
	pid_t	pid;
	int		status;

	cmd = ft_split(avc, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd("command not found\n", 2);
		free_chars(cmd);
		exit(CMD_NOT_FOUND);
	}
	pid = fork();
	if (pid == -1)
		return (free_s(path, cmd));
	if (pid == 0)
	{
		execve(path, cmd, envp);
		ft_putstr_fd("failed exec", 2);
		free_s(path, cmd);
		exit(EXEC_FAIL);
	}
	waitpid(pid, &status, 0);
	free_s(path, cmd);
}

// int	minicmd_main(int ac, char **av, char **envp)
// {
// 	char	*input;

// 	(void)ac;
// 	(void)av;
// 	while (1)
// 	{
// 		input = readline("cmd-demo> ");
// 		if (!input)
// 		{
// 			free(envp);
// 			break ;
// 		}
// 		else if (ft_strncmp(input, "echo -n ", 8) == 0)
// 			ft_echo(input + 8, 1);
// 		else if (ft_strncmp(input, "echo ", 5) == 0)
// 			ft_echo(input + 5, 0);
// 		else if (ft_strncmp(input, "cd ", 3) == 0)
// 			cd(input + 3);
// 		else if (ft_strncmp(input, "exit", 4) == 0)
// 		{
// 			free(envp);
// 			ft_exit(input + 5);
// 		}
// 		else if (ft_strncmp(input, "pwd", 3) == 0)
// 			pwd();
// 		else if (ft_strncmp(input, "env", 3) == 0)
// 			env(envp);
// 		else if (ft_strncmp(input, "export ", 7) == 0)
// 			export(input + 7, &envp);
// 		else if (ft_strncmp(input, "unset", 5) == 0)
// 			unset(input + 6, &envp);
// 		else
// 			execute(input, envp);
// 		free(input);
// 	}
// 	return (0);
// }
