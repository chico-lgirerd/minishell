/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:21:44 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/19 14:18:23 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <errno.h>
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

	if (!pipes || !(*pipes))
		return ;
	i = 0;
	while (i < n)
	{
		if (pipes[i][0] > 2)
			close(pipes[i][0]);
		if (pipes[i][1] > 2)
			close(pipes[i][1]);
		free(pipes[i]);
		pipes[i] = NULL;
		i++;
	}
	if (pipes)
		free(pipes);
	pipes = NULL;
}

int	**create_pipes(t_data *data, int n)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * n);
	if (!pipes)
		exit_pipeline(data, errno);
	i = 0;
	while (i < n)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			exit_pipeline(data, errno);
		if (pipe(pipes[i]) == -1)
			exit_pipeline(data, errno);
		i++;
	}
	return (pipes);
}
