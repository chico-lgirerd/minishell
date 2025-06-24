/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:53:13 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/24 13:22:20 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef struct s_data	t_data;

int		handle_not_found(char *cmd, t_data *data);
int		handle_nofile(char *cmd, t_data *data);
int		handle_noperm(char *cmd, t_data *data);
int		handle_point(t_data *data);
int		quote_unclosed(char *line);

#endif
