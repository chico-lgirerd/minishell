/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:12:06 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/20 19:15:59 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	rl_done = 1;
	g_signal = signum;
}

void	signal_handler_exec(int signum)
{
	g_signal = signum;
}
