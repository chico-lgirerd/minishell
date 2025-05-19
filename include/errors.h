/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:53:13 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/19 13:28:44 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <unistd.h>
# include <errno.h>
# include <string.h>
# include "parsing.h"
# include "pipes.h"

int		output_cd_error(int errcode);
int		handle_not_found(char *cmd, t_data *data);
int		handle_nofile(char *cmd, t_data *data);
int		handle_noperm(char *cmd, t_data *data);
int		handle_point(t_data *data);
void	handle_other_path(char *path, char *cmd, t_data *data, char **env);

#endif
