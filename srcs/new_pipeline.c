/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:01:19 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/09 17:10:32 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "pipes.h"

int	execute_pipeline(t_command *first_cmd, t_data *data)
{
	t_fork	params;
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
	params.pipes = pipes;
	params.pids = pids;
	params.num_cmds = num_cmds;
}
