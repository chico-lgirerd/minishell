/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:54:15 by tiaperei          #+#    #+#             */
/*   Updated: 2025/03/31 17:39:58 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "color.h"
#include "libft.h"

char	*cwd = NULL;

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
		printf("sigaction failed\n");
		exit(EXIT_FAILURE);
	}
}

void	sigint_handler(int signum)
{
	const char	*cyan = "\033[0;36m";
	const char	*reset ="\033[0m" ;
	
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, cyan, 7);
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, reset, 4);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	loop(void)
{
	char	*line;
	char	buff[BUFSIZ];
	
	ft_sigaction(SIGINT, sigint_handler, false);
	while (1)
	{
		cwd = getcwd(buff, sizeof(buff));
		if (!cwd)
			perror(RED"getcwd FAILED"RESET);
		printf(CYAN"%s"RESET, cwd);
		line = readline("$>");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		add_history(line);
		free(line);
	}
}

int	main(int argc, char **argv)
{
	
	(void)argc;
	(void)argv;
	loop();
	return (0);	
}
