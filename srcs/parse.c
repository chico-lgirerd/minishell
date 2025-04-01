/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:54:15 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/01 19:05:40 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "color.h"
#include "signals.h"
#include "utils.h"

int		g_exit_value = 0;
char	*g_cwd = NULL;

void	init_args(t_args_list *args)
{
	args->content = NULL;
	args->next = NULL;
	args->prev = NULL;
}

void	init_data(t_data *data)
{
	data->line = NULL;
	data->args = malloc(sizeof(t_args_list));
	if (!data->args)
		perror(RED"malloc failed"RESET);
	init_args(data->args);
}

void	parsing_args(t_args_list *args, char *line)
{
	args->content = ft_split(line, ' ');
}

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
		init_args(data->args);
		parsing_args(data->args, data->line);
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
 	//data.args = malloc(sizeof(t_data));
	//ft_memset(data.args, 0, sizeof(t_data));
	loop(&data);
	free_all_data(&data);
	return (0);
}
