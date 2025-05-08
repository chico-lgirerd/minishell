/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:01:40 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/08 15:55:58 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cmd.h"
#include "pipes.h"
#include "minishell.h"
#include "builtins.h"

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

void	exit_pipeline(pid_t *pids, int **pipes, int i, t_data *data)
{
	char	*args[2];

	args[0] = "1";
	args[1] = NULL;
	if (pipes)
		close_free_pipes(pipes, i);
	if (pids)
		free(pids);
	ft_exit(args, data);
}

int	execute_pipeline(t_command *first_cmd, char ***envp, t_data *data)
{
	pid_t		*pids;
	int			**pipes;
	t_command	*current_cmd;
	int			i;
	int			status;

	first_cmd->number_cmds = count_commands(first_cmd);
	if (first_cmd->number_cmds == 1)
		execute_single(first_cmd, envp, data);
	pipes = create_pipes(first_cmd->number_cmds - 1);
	if (!pipes)
		exit_pipeline(NULL, pipes, first_cmd->number_cmds - 1, data);
	pids = malloc(sizeof(pid_t) * first_cmd->number_cmds);
	if (!pids)
		exit_pipeline(pids, pipes, first_cmd->number_cmds - 1, data);
	i = 0;
	current_cmd = first_cmd;
	while (i < first_cmd->number_cmds && current_cmd)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			exit_pipeline(pids, pipes, first_cmd->number_cmds - 1, data);
		if (pids[i] == 0)
		{
			setup_child_pipes(pipes, i, first_cmd->number_cmds);
			current_cmd->number_cmds = first_cmd->number_cmds;
			execute_command(current_cmd, envp, pipes, data);
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
