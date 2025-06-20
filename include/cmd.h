/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:38:05 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/20 12:37:50 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "parsing.h"
# include "pipes.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define CMD_NOT_FOUND 127
# define EXEC_FAIL 126

void	free_chars(char **chars);
char	*find_path(t_data *data, char *cmd, char **envp);
void	execute_command(t_command *cmd, t_fork *forks, t_data *data);
int		execute_single(t_command *cmd, t_data *data);
int		handle_empty_cmd(t_data *data, t_command *cmd);
void	handle_path(char *path, char *cmd, t_data *data, char **env_arr);
void	handle_other_path(char *path, char *cmd, t_data *data, char **env);
int		is_directory(char *path);
int		handle_isdir(char *cmd, t_data *data);
// int		finish_executing(int status, struct sigaction *original);
int		finish_executing(int status);

#endif
