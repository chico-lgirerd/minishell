/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:37:42 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 19:13:56 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

int	g_signal;

int	nothing(void)
{
	return (0);
}

void	handle_signal_child(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_signal_main(void)
{
	struct sigaction	sa;

	g_signal = 0;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_handler = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_signal_wait(void)
{
	struct sigaction	sa;

	g_signal = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_handler = signal_handler_exec;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
