/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:01:40 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/26 12:28:10 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cmd.h"
#include "minishell.h"

int	execute_pipeline(t_command *first_cmd, char ***envp)
{
	pid_t		*pids;
	int			**pipes;
	t_command	*current_cmd;
	int			i;
	int			status;

	first_cmd->number_cmds = count_commands(first_cmd);
	if (first_cmd->number_cmds)
		execute_command(first_cmd, envp);
	pipes = create_pipes(first_cmd->number_cmds - 1);
}
