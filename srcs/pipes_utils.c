/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:21:44 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/26 16:05:00 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <unistd.h>

int	count_commands(t_command *cmd)
{
	int			count;
	t_command	*current_cmd;

	count = 0;
	current_cmd = cmd;
	while (current_cmd)
	{
		count++;
		current_cmd = current_cmd->next;
	}
	return (count);
}

void	close_free_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pipes[i][0] > 2)
			close(pipes[i][0]);
		if (pipes[i][1] > 2)
			close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	pipes_error(int **pipes, int n)
{
	while (n >= 0)
	{
		free(pipes[n]);
		n--;
	}
	free(pipes);
	exit(10000);
}

int	**create_pipes(int n)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * n);
	if (!pipes)
		exit(10000);
	i = 0;
	while (i < n)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			pipes_error(pipes, i);
		if (pipe(pipes[i]) == -1)
			pipes_error(pipes, i);
		i++;
	}
	return (pipes);
}
