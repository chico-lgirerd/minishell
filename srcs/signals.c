/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:37:42 by tiaperei          #+#    #+#             */
/*   Updated: 2025/05/16 14:14:09 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "minishell.h"
#include "libft.h"
#include "utils.h"

void	manage_signals(void)
{
	ft_sigaction(SIGINT, sigint_handler, false);
	ft_sigaction(SIGSEGV, sigsegv_handler, false);
	ft_sigaction(SIGQUIT, SIG_IGN, false);
}

void	sigint_handler(int signum)
{
	(void)signum;
	g_exit_value = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigsegv_handler(int signum)
{
	(void)signum;
	g_exit_value = 139;
	write(STDERR_FILENO, "noob\n", 5);
	exit(EXIT_FAILURE);
}
