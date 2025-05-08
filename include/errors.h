/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:53:13 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/08 14:39:47 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <unistd.h>
# include <errno.h>
# include <string.h>
# include "parsing.h"

int	output_error(int errcode);
int	handle_not_found(char *cmd, t_command *first_cmd);
int	handle_nofile(char *cmd, t_command *first_cmd);
int	handle_noperm(char *cmd, t_command *first_cmd);
int	handle_point(t_command *first_cmd);

#endif
