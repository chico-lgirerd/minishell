/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:01:40 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/09 18:12:13 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cmd.h"
#include "pipes.h"
#include "minishell.h"
#include "builtins.h"





// static int	execute_old_pipeline(t_command *first_cmd, char ***envp, t_data *data)
// {
// 	pid_t		*pids;
// 	int			**pipes;
// 	t_command	*current_cmd;
// 	int			i;
// 	int			status;

// 	first_cmd->number_cmds = count_commands(first_cmd);
// 	pipes = create_pipes(first_cmd->number_cmds - 1);
// 	if (!pipes)
// 		exit_pipeline(NULL, pipes, first_cmd->number_cmds - 1, data);
// 	pids = malloc(sizeof(pid_t) * first_cmd->number_cmds);
// 	if (!pids)
// 		exit_pipeline(pids, pipes, first_cmd->number_cmds - 1, data);
// 	i = 0;
// 	current_cmd = first_cmd;
// 	while (i < first_cmd->number_cmds && current_cmd)
// 	{
// 		pids[i] = fork();
// 		if (pids[i] == -1)
// 			exit_pipeline(pids, pipes, first_cmd->number_cmds - 1, data);
// 		if (pids[i] == 0)
// 		{
// 			setup_child_pipes(pipes, i, first_cmd->number_cmds);
// 			current_cmd->number_cmds = first_cmd->number_cmds;
// 			execute_command(current_cmd, envp, pipes, data);
// 			exit(1);
// 		}
// 		current_cmd = current_cmd->next;
// 		i++;
// 	}
// 	close_free_pipes(pipes, first_cmd->number_cmds - 1);
// 	i = 0;
// 	status = 0;
// 	while (i < first_cmd->number_cmds)
// 	{
// 		if (i == first_cmd->number_cmds - 1)
// 			waitpid(pids[i], &status, 0);
// 		else
// 			waitpid(pids[i], NULL, 0);
// 		i++;
// 	}
// 	free(pids);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	return (1);
// }
