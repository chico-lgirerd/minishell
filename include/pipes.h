/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:23:03 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/04 17:45:23 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "parsing.h"

typedef struct s_command	t_command;
typedef struct s_data		t_data;

typedef struct s_fork
{
	int		**pipes;
	pid_t	*pids;
	int		num_cmds;
}	t_fork;

int		count_commands(t_command *cmd);
void	close_free_pipes(int **pipes, int n);
int		**create_pipes(t_data *data, int n);
int		execute_pipeline(t_command *first_cmd, t_data *data);
int		exit_pipeline(t_data *data, int errcode);

#endif
