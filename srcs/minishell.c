/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:51:52 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/18 11:17:37 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parsing.h"
#include "signals.h"
#include "colors.h"
#include "utils.h"
#include "builtins.h"
#include "pipes.h"
#include "cmd.h"
#include "files.h"

char	*get_new_prompt(t_data *data, char *prompt)
{
	char	*tmp;
	char	*path;
	char	*exit_value;
	char	*home;
	char	cwd[PATH_MAX];

	home = get_env_value("HOME", data->env);
	if (!home)
		home = "#";
	if (getcwd(cwd, sizeof(cwd)) == 0)
		return (NULL);
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		tmp = ft_strjoin3("[~", cwd + ft_strlen(home), "]");
	else
		tmp = ft_strjoin3("[", cwd, "]");
	path = ft_strjoin3(CYAN, tmp, RESET);
	free(tmp);
	exit_value = ft_itoa(data->exit_value);
	tmp = ft_strjoin3("[", exit_value, "]");
	free(exit_value);
	exit_value = ft_strjoin3(YELLOW, tmp, RESET);
	free(tmp);
	prompt = ft_strjoin3(path, exit_value, "$ ");
	free(path);
	free(exit_value);
	return (prompt);
}

void	execute_commands(t_data *data)
{
	if (data->first_cmd->args == NULL || data->first_cmd->args[0] == NULL)
		data->exit_value = handle_empty_cmd(data, data->first_cmd);
	else
	{
		if (pipe_in_tokens(data->args_list))
			data->exit_value = execute_pipeline(data->first_cmd, data);
		else if (is_builtin(data->first_cmd->args[0]))
			data->exit_value = run_builtins(data->first_cmd, data);
		else
			data->exit_value = execute_single(data->first_cmd, data);
	}
}

void	build_and_execute(t_data *data)
{
	build_command(data, data->args_list);
	if (data->first_cmd)
	{
		if (proc_heredoc(data, data->first_cmd) == 130)
		{
			free_command(&data->first_cmd);
			free_args_list(&data->args_list);
			free(data->line);
			return ;
		}
		execute_commands(data);
		free_command(&data->first_cmd);
	}
	free_args_list(&data->args_list);
	free(data->line);
}

static void	process_line(t_data *data)
{
	if (onlyspace(data->line))
	{
		free(data->line);
		return ;
	}
	parsing_args(data, data->line);
	add_history(data->line);
	if (validate_syntax(data, data->args_list) != 1)
	{
		free_args_list(&data->args_list);
		free_command(&data->first_cmd);
		return ;
	}
	build_and_execute(data);
}

void	loop(t_data *data, char *prompt)
{
	while (1)
	{
		g_signal = 0;
		manage_signals();
		prompt = get_new_prompt(data, prompt);
		data->line = readline(prompt);
		free(prompt);
		if (!data->line)
		{
			free_all_data(data, true);
			printf("exit\n");
			break ;
		}
		process_line(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*prompt;

	(void)argc;
	(void)argv;
	if (env[0] == NULL)
		return (1);
	init_data(&data, env);
	prompt = NULL;
	loop(&data, prompt);
	return (0);
}
