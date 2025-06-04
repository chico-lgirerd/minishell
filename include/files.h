/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:35:34 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/04 16:18:04 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_H
# define FILES_H

# include "parsing.h"
# include "pipes.h"

int		open_input(t_command *cmd, t_data *data, int *saved_fds);
int		open_output(t_command *cmd, t_data *data, int *saved_fds);
void	setup_redirection(t_command *cmd, t_data *data, int *saved_fds);
void	restore_fds(int *saved_fds, t_data *data);
void	heredoc(t_data *data, char *tempfile, char *delim);
int		proc_heredoc(t_data *data, t_command *cmd);
void	init_redir(t_command *cmd, char	*filename, int append_mode);
int		output_file_error(int errcode, char *filename, t_data *data);
int		dup_error(t_data *data, int errcode);

#endif
