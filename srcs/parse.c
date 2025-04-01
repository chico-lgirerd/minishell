/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:54:15 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/01 13:18:49 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "color.h"
#include "utils.h"

char	*g_cwd = NULL;

void	sigint_handler(int signum)
{
	const char	*cyan = "\033[0;36m";
	const char	*reset ="\033[0m" ;
	
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, cyan, 7);
	write(STDOUT_FILENO, g_cwd, ft_strlen(g_cwd));
	write(STDOUT_FILENO, reset, 4);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	loop(t_data *data)
{
	char	buff[PATH_MAX];
	
	manage_signal();
	ft_sigaction(SIGINT, sigint_handler, false);
	while (1)
	{
		g_cwd = getcwd(buff, sizeof(buff));
		if (!g_cwd)
			perror(RED"getcwd FAILED"RESET);
		printf(CYAN"%s"RESET, g_cwd);
		data->line = readline("$>");
		if (!data->line)
		{
			printf("exit\n");
			break;
		}
		if (data->line[0] == '\0')
		{
			free(data->line);
			continue;
		}
		add_history(data->line);
		free(data->line);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	data.args = malloc(sizeof(t_data));
	loop(&data);
	return (0);
}
