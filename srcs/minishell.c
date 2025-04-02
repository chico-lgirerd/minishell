/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:51:52 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/02 18:14:56 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "signals.h"
#include "color.h"

int		g_exit_value = 0;
char	*g_cwd = NULL;

void	loop(t_data *data)
{
	char	buff[PATH_MAX];

	manage_signals();
	while (1)
	{
		g_cwd = getcwd(buff, sizeof(buff));
		//g_cwd = getcwd(buff, 1);
		if (!g_cwd)
			perror(RED"getcwd failed"RESET);
		printf(CYAN"%s"RESET, g_cwd);
		data->line = readline("$>");
		if (!data->line)
		{
			printf("exit\n");
			break ;
		}
		if (data->line[0] == '\0')
		{
			free(data->line);
			continue ;
		}
		parsing_args(&(data->args_list), data->line);
		//print_list(data->args_list);
		free_args_list(&data->args_list);
		add_history(data->line);
		free(data->line);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_data(&data);
	loop(&data);
	free_all_data(&data);
	return (0);
}