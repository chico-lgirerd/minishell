/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:51:52 by tiaperei          #+#    #+#             */
/*   Updated: 2025/05/17 17:24:17 by lgirerd          ###   ########lyon.fr   */
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

int	g_exit_value;

char	*get_new_prompt(char *prompt)
{
	char	*tmp;
	char	*path;
	char	*exit_value;
	char	*home;
	char	cwd[PATH_MAX];

	exit_value = ft_itoa(g_exit_value);
	//exit_value = NULL;
	home = getenv("HOME");
	//home = NULL;
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

int	validate_syntax(t_args *args_list)
{
	t_args	*cur;

	cur = args_list;
	if (!args_list)
		return (1);
	while (cur)
	{
		if ((token_is_pipe(cur->content) && (!cur->quoted)) && (!cur->next || !cur->next->content))
		{
			printf("syntax error near unexpected token `|'\n");
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}

void	loop(t_data *data)
{
	char	*prompt;

	prompt = NULL;
	manage_signals();
	while (1)
	{
		prompt = get_new_prompt(prompt);
		data->line = readline(prompt);
		free(prompt);
		if (!data->line)
		{
			free_all_data(data);
			printf("exit\n");
			break ;
		}
		if (onlyspace(data->line))
		{
			free(data->line);
			g_exit_value = 0;
			continue ;
		}
		parsing_args(data, data->line);
		if (!validate_syntax(data->args_list))
		{
			free_all_data(data);
			continue;
		}
		build_command(data, data->args_list);
		// print_command(data->first_cmd);
		if (data->first_cmd)
		{
			// copy_env(data, data->env); // check fail
			if (pipe_in_tokens(data->args_list))
				g_exit_value = execute_pipeline(data->first_cmd, data);
			else if (is_builtin(data->first_cmd->args[0]))
				g_exit_value = run_builtins(data->first_cmd, data);
			else
				g_exit_value = execute_single(data->first_cmd, data);
			free_command(&data->first_cmd);
		}
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
	init_data(&data, env);
	loop(&data);
	//free_all_data(&data);
	return (0);
}
