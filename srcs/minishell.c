/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:51:52 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/25 18:53:38 by lgirerd          ###   ########lyon.fr   */
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
#include "errors.h"
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	execute_commands(t_data *data)
{
	if (g_signal != 0)
	{
		g_signal = 0;
		rl_on_new_line();
		rl_replace_line("", 0);
	}
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

void    print_command(t_command *head)
{
    t_command    *current;
    int            i;

    current = head;
    while (current)
    {
        printf("Command with %d args:\n", current->count_args);
        for (i = 0; i < current->count_args; i++)
        {
            printf("  args[%d]: %s\n", i, current->args[i]);
        }
        printf("input_file: %s\n", current->input_file);
        if (current->out_redir)
        {
            printf("first out redir: %s\n", current->out_redir->filename);
            printf("append mode : %d\n", current->out_redir->append);
        }
        if (current->heredocs)
            printf("heredoc_delimiter: %s\n", current->heredocs->delim);
        printf("\n");
        current = current->next;
    }
}

static void	build_and_execute(t_data *data)
{
	build_command(data, data->args_list);
	print_command(data->first_cmd);
	if (data->first_cmd)
	{
		if (data->first_cmd->args == NULL || data->first_cmd->args[0] == NULL)
		{
			data->exit_value = handle_empty_cmd(data, data->first_cmd);
			free_command(&data->first_cmd);
		}
		if (heredoc_in_tokens(data->args_list))
		{
			data->exit_value = proc_heredoc(data, data->first_cmd);
			if (data->exit_value != 0)
			{
				free_command(&data->first_cmd);
				return ;
			}
		}
		execute_commands(data);
		free_command(&data->first_cmd);
	}
}

static void	process_line(t_data *data)
{
	if (onlyspace(data->line))
		return ;
	parsing_args(data, data->line);
	add_history(data->line);
	if (quote_unclosed(data->line))
	{
		ft_putendl_fd(RED"error: quote not closed"RESET, 2);
		data->exit_value = 2;
		return ;
	}
	if (validate_syntax(data, data->args_list) != 1)
	{
		free_args_list(&data->args_list);
		return ;
	}
	build_and_execute(data);
	free_args_list(&data->args_list);
}

static void	loop(t_data *data, char *prompt)
{
	while (1)
	{
		g_signal = 0;
		handle_signal_main();
		rl_on_new_line();
		prompt = get_new_prompt(data, prompt);
		data->line = readline(prompt);
		free(prompt);
		if (!data->line)
		{
			free_all_data(data, true);
			printf("exit\n");
			break ;
		}
		if (g_signal == SIGINT)
		{
			free(data->line);
			data->exit_value = 130;
			continue ;
		}
		process_line(data);
		free(data->line);
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
	rl_event_hook = &nothing;
	prompt = NULL;
	loop(&data, prompt);
	return (0);
}
