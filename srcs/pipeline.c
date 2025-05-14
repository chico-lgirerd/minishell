/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:01:19 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/14 15:59:24 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "pipes.h"
#include "cmd.h"

static void	setup_child_pipes(int **pipes, int i, int cmd_count)
{
	int	j;

	if (i > 0)
		if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
			exit(10000);
	if (i < cmd_count - 1)
		if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
			exit(10000);
	j = 0;
	while (j < cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

static void	exit_pipeline(pid_t *pids, int **pipes, int i, t_data *data)
{
	if (pipes)
		close_free_pipes(pipes, i);
	if (pids)
		free(pids);
	free_all_data(data);
	exit(1);
}

void	fork_commands(t_command *first_cmd, t_fork *forks, t_data *data)
{
	t_command	*curr;
	int			i;

	curr = first_cmd;
	i = 0;
	while (i < forks->num_cmds && curr)
	{
		forks->pids[i] = fork();
		if (forks->pids[i] == -1)
			exit_pipeline(forks->pids, forks->pipes, i, data);
		if (forks->pids[i] == 0)
		{
			setup_child_pipes(forks->pipes, i, forks->num_cmds);
			curr->number_cmds = forks->num_cmds;
			execute_command(curr, forks, data);
			exit(1);
		}
		curr = curr->next;
		i++;
	}
}

static int	wait_childs(pid_t *pids, int num_cmds)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < num_cmds)
	{
		if (i == num_cmds - 1)
			waitpid(pids[i], &status, 0);
		else
			waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_pipeline(t_command *first_cmd, t_data *data)
{
	t_fork	forks;
	int		**pipes;
	pid_t	*pids;
	int		num_cmds;

	num_cmds = count_commands(first_cmd);
	first_cmd->number_cmds = num_cmds;
	pipes = create_pipes(num_cmds - 1);
	if (!pipes)
		exit_pipeline(NULL, pipes, num_cmds - 1, data);
	pids = malloc(sizeof(pid_t) * num_cmds);
	if (!pids)
		exit_pipeline(pids, pipes, num_cmds, data);
	forks.num_cmds = num_cmds;
	forks.pipes = pipes;
	forks.pids = pids;
	fork_commands(first_cmd, &forks, data);
	close_free_pipes(forks.pipes, num_cmds - 1);
	return (wait_childs(forks.pids, num_cmds));
}
