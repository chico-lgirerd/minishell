/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:32:31 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/11 17:13:11 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <unistd.h>
# include <signal.h>
# include <stdbool.h>

void	ft_sigaction(int signum, void *handler, bool use_siginfo);
void	manage_signals(void);
void	manage_signals_in_process(void);
void	sigint_handler(int signum);
void	sigsegv_handler(int signum);
void	setup_signals_parent(struct sigaction *orig, struct sigaction *ignore);
void	setup_heredoc_signals(void);
void	sigint_process_handler(int signum);

#endif
