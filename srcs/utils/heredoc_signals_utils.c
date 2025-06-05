/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:43:58 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/05 16:45:03 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
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
	ft_sigaction(SIGINT, heredoc_sigint_handler, false);
	ft_sigaction(SIGQUIT, SIG_IGN, false);
}
