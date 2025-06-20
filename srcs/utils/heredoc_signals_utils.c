/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:43:58 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/20 19:16:47 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	g_signal = SIGINT;
	close(0);
	rl_done = 1;
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
