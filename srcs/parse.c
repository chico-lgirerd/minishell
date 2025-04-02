/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:54:15 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/02 17:15:06 by tiaperei         ###   ########.fr       */
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
	data->args_list = malloc(sizeof(t_args_list));
	if (!data->args_list)
		perror(RED"malloc failed"RESET);
	init_args(data->args_list);
}

void	append_node(t_args_list **args, char *content)
{
	t_args_list	*node;
	t_args_list	*last_node;

	node = malloc(sizeof(t_args_list));
	if (!node)
		perror(RED"getcwd failed"RESET);
	node->next = NULL;
	node->prev = NULL;
	node->content = content;
	if (!(*args))
		*args = node;
	else
	{
		last_node = ft_lstlast(*args);
		last_node->next = node;
		node->prev = last_node;
	}
}

void	parsing_args(t_args_list **args_list, char *line)
{
	char	**args;
	int		i;

	args = ft_split(line, ' ');
	i = 0;
	while (args[i])
	{
		append_node(args_list, ft_strdup(args[i]));
		i++;
	}
	free_args(args);
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
