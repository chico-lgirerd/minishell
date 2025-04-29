/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:23:03 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/29 14:29:18 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include <unistd.h>
# include "parsing.h"

int		count_commands(t_command *cmd);
void	close_free_pipes(int **pipes, int n);
int		**create_pipes(int n);
int		execute_pipeline(t_command *first_cmd, char ***envp, t_data *data);

#endif
