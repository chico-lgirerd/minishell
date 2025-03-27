/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:54:15 by tiaperei          #+#    #+#             */
/*   Updated: 2025/03/27 17:19:27 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	ft_sigaction(int signum, void *handler, bool use_siginfo)
{
	struct sigaction	sa;

	if (use_siginfo == true)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handler;
	}
	else
		sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signum, &sa, NULL) == -1)
	{
		ft_printf("sigaction failed\n");
		exit(EXIT_FAILURE);
	}
}

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(void)
{
	char *input_line;

	ft_sigaction(SIGINT, sigint_handler, true);
	while (1)
	{
		input_line = readline("minishell > ");
		if (!input_line)
		{
			ft_printf("exit\n");
			break;
		}
		if (*input_line == '\0')
		{
			free(input_line);
			continue;
		}
		add_history(input_line);
		ft_printf("read line: %s\n", input_line);
		free(input_line);
	}
	return 0;
}
