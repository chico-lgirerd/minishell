/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:38:05 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/08 17:39:38 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "parsing.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define CMD_NOT_FOUND 127
# define EXEC_FAIL 126

void	free_chars(char **chars);
void	free_s(char *str, char **sstr);
int		open_input(t_command *cmd, t_data *data);
int		open_output(t_command *cmd, t_data *data);
char	*find_path(char *cmd, char **envp);
void	execute_command(t_command *cmd, char ***envp, int **pipes,
			t_data *data);
int		execute_single(t_command *cmd, char ***envp, t_data *data);

#endif
