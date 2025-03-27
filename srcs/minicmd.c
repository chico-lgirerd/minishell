/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:13:20 by lgirerd           #+#    #+#             */
/*   Updated: 2025/03/27 18:37:15 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minicmd.h"
#include <fcntl.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

void	free_chars(char **chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		free(chars[i]);
		i++;
	}
	free(chars);
}

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
		ft_putstr_fd("command not found\n" ,2);
		free_chars(cmd);
		exit(CMD_NOT_FOUND);
	}
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		execve(path, cmd, envp);
		ft_putstr_fd("failed exec", 2);
		free(path);
		free_chars(cmd);
		exit(EXEC_FAIL);
	}
	waitpid(pid, &status, 0);
	free(path);
	free_chars(cmd);
	exit(WEXITSTATUS(status));
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	pid_t	pid1;
	int		status;

	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("cmd-demo> ");
		if (!input)
			break ;
		pid1 = fork();
		if (pid1 == -1)
			exit(1);
		if (pid1 == 0)
		{
			if (ft_strcmp(input, "echo") == 0)
				ft_echo(av, envp);
			else
				execute(input, envp);
		}
		waitpid(pid1, &status, 0);
		free(input);
	}
	return (0);
}
