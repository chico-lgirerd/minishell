/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:32:31 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/24 13:22:50 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	handle_signal_child(void);
void	handle_signal_wait(void);
void	handle_signal_main(void);
void	handle_signal_child_heredoc(void);
int		nothing(void);
void	signal_handler(int signum);
void	signal_handler_exec(int signum);

#endif
