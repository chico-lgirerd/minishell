/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:51:52 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/18 16:52:55 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parsing.h"
#include "signals.h"
#include "color.h"
#include "utils.h"

int	g_exit_value;

char	*get_new_prompt(char *prompt)
{
	char	*tmp;
	char	*path;
	char	*exit_value;
	char	*home;
	char	cwd[PATH_MAX];

	exit_value = ft_itoa(g_exit_value);
	home = getenv("HOME");
	if (getcwd(cwd, sizeof(cwd)) == 0)
		return (NULL);
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		tmp = ft_strjoin3("[~", cwd + ft_strlen(home), "]");
	else
		tmp = ft_strjoin3("[", cwd, "]");
	path = ft_strjoin3(CYAN, tmp, RESET);
	free(tmp);
	tmp = ft_strjoin3("[", exit_value, "]");
	free(exit_value);
	exit_value = ft_strjoin3(RED, tmp, RESET);
	free(tmp);
	prompt = ft_strjoin3(path, exit_value, "$>");
	free(path);
	free(exit_value);
	return (prompt);
}

void	loop(t_data *data, char **env)
{
	char	*prompt;

	(void)env;
	prompt = NULL;
	manage_signals();
	while (1)
	{
		prompt = get_new_prompt(prompt);
		data->line = readline(prompt);
		free(prompt);
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
		data->args_list->first_cmd = build_command(&data->args_list);
		print_command(data->args_list->first_cmd);
		free_command(&data->args_list->first_cmd);
		//if (data->args_list->first_cmd)
			//exec();
		free_args_list(&data->args_list);
		add_history(data->line);
		free(data->line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_data(&data);
	loop(&data, env);
	free_all_data(&data);
	return (0);
}
