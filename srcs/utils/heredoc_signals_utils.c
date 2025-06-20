/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:43:58 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/20 16:15:58 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "minishell.h"

#include "libft.h"

void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	g_signal = SIGINT;
	// write(1, "\n", 1);
	close(0);
	rl_done = 1;
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

void	handle_signal_child_heredoc(void)
{
	struct sigaction	sa;

	g_signal = 0;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = heredoc_sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);	
}
