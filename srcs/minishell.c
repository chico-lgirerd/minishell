/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:51:52 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/03 13:34:06 by lgirerd          ###   ########lyon.fr   */
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
#include "errors.h"

int	g_exit_value;

char	*get_new_prompt(char *prompt)
{
	char	*tmp;
	char	*path;
	char	*exit_value;
	char	*home;
	char	cwd[PATH_MAX];

	home = getenv("HOME");
	if (getcwd(cwd, sizeof(cwd)) == 0)
		return (NULL);
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		tmp = ft_strjoin3("[~", cwd + ft_strlen(home), "]");
	else
		tmp = ft_strjoin3("[", cwd, "]");
	path = ft_strjoin3(CYAN, tmp, RESET);
	free(tmp);
	exit_value = ft_itoa(g_exit_value);
	tmp = ft_strjoin3("[", exit_value, "]");
	free(exit_value);
	exit_value = ft_strjoin3(YELLOW, tmp, RESET);
	free(tmp);
	prompt = ft_strjoin3(path, exit_value, "$ ");
	free(path);
	free(exit_value);
	return (prompt);
}

int	validate_syntax(t_args *args_list)
{
	t_args	*cur;

	cur = args_list;
	while (cur)
	{
		if ((token_is_pipe(cur->content) && !cur->in_quote)
				&& (!cur->prev || !cur->next || !cur->next->content
				|| token_is_pipe(cur->next->content)))
		{
			print_syntax_error("|", 2);
			g_exit_value = 2;
			return (0);
		}
		if ((token_is_redirection(cur->content) && !cur->in_quote)
				&& (!cur->next || !cur->next->content
				|| token_is_redirection(cur->next->content)))
		{
			if (cur->next)
				print_syntax_error(cur->next->content, 2);
			else
				print_syntax_error("newline", 2);
			g_exit_value = 2;
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}

int	handle_heredoc_before_exec(t_data *data)
{
	if (proc_heredoc(data, data->first_cmd))
	{
		free_command(&data->first_cmd);
		free_args_list(&data->args_list);
		free(data->line);
		return (1);
	}
	return (0);
}

void	build_and_execute(t_data *data, char **env)
{
	build_command(data, data->args_list);
	if (data->first_cmd)
	{
		//print_command(data->first_cmd);
		if (data->first_cmd->args == NULL || data->first_cmd->args[0] == NULL
			|| data->first_cmd->args[0][0] == '\0')
			g_exit_value = handle_empty_cmd(data, data->first_cmd, env);
		if (handle_heredoc_before_exec(data))
			return ;
		if (!data->first_cmd->args || data->first_cmd->args[0][0] == '\0')
			g_exit_value = handle_empty_cmd(data, data->first_cmd);
		else
		{
			if (pipe_in_tokens(data->args_list))
				g_exit_value = execute_pipeline(data->first_cmd, data);
			else if (is_builtin(data->first_cmd->args[0]))
				g_exit_value = run_builtins(data->first_cmd, data);
			else
				g_exit_value = execute_single(data->first_cmd, data);
		}
		free_command(&data->first_cmd);
	}
	free_args_list(&data->args_list);
	free(data->line);
}

void	loop(t_data *data, char *prompt, char **env)
{
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
			continue ;
		}
		parsing_args(data, data->line);
		print_list(data->args_list);
		add_history(data->line);
		if (!validate_syntax(data->args_list))
		{
			free_command(&data->first_cmd);
			free_args_list(&data->args_list);
			continue ;
		}
		build_and_execute(data, env);
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
	manage_signals();
	init_data(&data, env);
	prompt = NULL;
	loop(&data, prompt, env);
	return (0);
}
