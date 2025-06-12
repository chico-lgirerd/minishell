/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:43:58 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/12 17:04:44 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "minishell.h"

void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	g_signal = 2;
	write(1, "\n", 1);
	close(0);
}

void	ignore_sigint(int signum)
{
	(void)signum;
}

void	setup_heredoc_signals(void)
{
	g_signal = 0;
	ft_sigaction(SIGINT, heredoc_sigint_handler, false);
	ft_sigaction(SIGQUIT, SIG_IGN, false);
}

void	setup_signals_parent(struct sigaction *orig, struct sigaction *ignore)
{
	sigaction(SIGINT, NULL, orig);
	*ignore = *orig;
	ignore->sa_handler = SIG_IGN;
	sigemptyset(&ignore->sa_mask);
	ignore->sa_flags = 0;
	sigaction(SIGINT, ignore, NULL);
}

