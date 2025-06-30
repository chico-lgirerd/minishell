/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:35:34 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/30 17:07:19 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_H
# define FILES_H

typedef struct s_data		t_data;
typedef struct s_command	t_command;
typedef struct s_heredoc	t_heredoc;

int		open_input(t_command *cmd, t_data *data, int *saved_fds);
int		open_output(t_command *cmd, t_data *data, int *saved_fds);
void	setup_redirection(t_command *cmd, t_data *data, int *saved_fds);
void	restore_fds(int *saved_fds, t_data *data);
int		proc_heredoc(t_data *data, t_command *cmd);
int		output_file_error(int errcode, char *filename, t_data *data);
int		dup_error(t_data *data, int errcode);
int		create_temp_file(t_heredoc *curr);
void	open_heredoc(t_data *data, t_command *cmd, int *saved_fds);
void	check_for_output(t_command *cmd, t_data *data, int *saved_fds);

#endif
