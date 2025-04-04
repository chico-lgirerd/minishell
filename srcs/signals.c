/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:37:42 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/04 17:20:45 by tiaperei         ###   ########.fr       */
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
	const char	*cyan;
	const char	*reset;

	(void)signum;
	cyan = "\033[0;36m";
	reset = "\033[0m";
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, cyan, 7);
	write(STDOUT_FILENO, g_cwd, ft_strlen(g_cwd));
	write(STDOUT_FILENO, reset, 4);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_value = 130;
}

void	sigsegv_handler(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "noob\n", 5);
	exit(EXIT_FAILURE);
	g_exit_value = 139;
}
