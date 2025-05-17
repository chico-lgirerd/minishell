/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:38:05 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/17 17:24:08 by lgirerd          ###   ########lyon.fr   */
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
void	free_s(char *str, char **sstr);
char	*find_path(char *cmd, char **envp);
void	execute_command(t_command *cmd, t_fork *forks, t_data *data);
int		execute_single(t_command *cmd, t_data *data);

#endif
