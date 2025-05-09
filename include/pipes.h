/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:23:03 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/09 17:08:06 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include <unistd.h>
# include <sys/types.h>
# include "parsing.h"

typedef struct s_fork
{
	int		**pipes;
	pid_t	*pids;
	int		num_cmds;
}	t_fork;

int		count_commands(t_command *cmd);
void	close_free_pipes(int **pipes, int n);
int		**create_pipes(int n);
int		execute_pipeline(t_command *first_cmd, char ***envp, t_data *data);

#endif
