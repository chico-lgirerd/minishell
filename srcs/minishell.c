/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:51:52 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/05 15:49:52 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "signals.h"
#include "color.h"
#include "utils.h"

int		g_exit_value = 0;

char	*get_prompt(void)
{
	char	*prompt;
	char	cwd[PATH_MAX];

	prompt = "";
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		prompt = ft_strjoin3(CYAN, cwd, RESET);
	return (prompt);
}

void	loop(t_data *data)
{
	manage_signals();
	while (1)
	{
		data->line = readline(get_prompt());
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
		parsing_args(&data->args_list, data->line);
		print_list(data->args_list);
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