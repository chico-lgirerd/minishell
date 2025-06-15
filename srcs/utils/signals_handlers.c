/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:12:06 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/15 17:17:38 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

#include <sys/ioctl.h>

void	sigint_process_handler(int signum)
{
	(void)signum;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
}

void	sigint_handler(int signum)
{
	(void)signum;
	g_signal = 2;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigsegv_handler(int signum)
{
	(void)signum;
	g_signal = 11;
	exit(139);
}

void	sigquit_process_handler(int signum)
{
	(void)signum;
	g_signal = SIGQUIT;
	exit(131);
}
