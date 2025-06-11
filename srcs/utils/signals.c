/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:37:42 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/11 17:12:25 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "minishell.h"
#include "utils.h"
#include "libft.h"
#include "colors.h"

int	g_signal;

void	manage_signals(void)
{
	ft_sigaction(SIGINT, sigint_handler, false);
	ft_sigaction(SIGSEGV, sigsegv_handler, false);
	ft_sigaction(SIGQUIT, SIG_IGN, false);
}

void	manage_signals_in_process(void)
{
	ft_sigaction(SIGINT, sigint_process_handler, false);
	ft_sigaction(SIGSEGV, sigsegv_handler, false);
	ft_sigaction(SIGQUIT, SIG_DFL, false);
}

void	ft_sigaction(int signum, void *handler, bool use_siginfo)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (use_siginfo == true)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handler;
	}
	else
		sa.sa_handler = handler;
	if (sigaction(signum, &sa, NULL) == -1)
	{
		ft_putendl_fd(RED"minishell: sigaction failed"RESET, 2);
		exit(EXIT_FAILURE);
	}
}
