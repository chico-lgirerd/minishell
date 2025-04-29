/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:38:05 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/29 14:29:56 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "parsing.h"
# include <fcntl.h>
# include <stdlib.h>
# include <wait.h>
# include <unistd.h>

# define CMD_NOT_FOUND 127
# define EXEC_FAIL 126

void	free_chars(char **chars);
void	free_s(char *str, char **sstr);
int		open_input(t_command *cmd);
int		open_output(t_command *cmd);
char	*find_path(char *cmd, char **envp);
void	execute_command(t_command *cmd, char ***envp, int **pipes, t_data *data);
int		execute_single(t_command *cmd, char ***envp);

#endif
