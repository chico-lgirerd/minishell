/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:01:40 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/26 15:39:19 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cmd.h"
#include "pipes.h"
#include "minishell.h"

void	setup_child_pipes(int **pipes, int i, int cmd_count)
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

int	execute_pipeline(t_command *first_cmd, char ***envp)
{
	pid_t		*pids;
	int			**pipes;
	t_command	*current_cmd;
	int			i;
	int			status;

	first_cmd->number_cmds = count_commands(first_cmd);
	if (first_cmd->number_cmds)
		execute_single(first_cmd, envp);
	pipes = create_pipes(first_cmd->number_cmds - 1);
	pids = malloc(sizeof(pid_t) * first_cmd->number_cmds);
	if (!pids)
		// close & free pipes
		exit(10000);
	i = 0;
	current_cmd = first_cmd;
	while (i < first_cmd->number_cmds && current_cmd)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			//close & free pipes & pids
			exit(10000);
		if (pids[i] == 0)
		{
			setup_child_pipes(pipes, i, first_cmd->number_cmds);
			if (current_cmd->prev)
				current_cmd->input_file = current_cmd->prev->output_file;
			execute_command(current_cmd, envp, pipes, first_cmd->number_cmds - 1);
			exit(1);
		}
		current_cmd = current_cmd->next;
		i++;
	}
	close_free_pipes(pipes, first_cmd->number_cmds - 1);
	i = 0;
	status = 0;
	while (i < first_cmd->number_cmds)
	{
		if (i == first_cmd->number_cmds - 1)
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
