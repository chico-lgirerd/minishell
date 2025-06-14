/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:51:52 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/14 17:25:29 by tiaperei         ###   ########.fr       */
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

static char	*get_new_prompt(t_data *data, char *prompt)
{
	char	*tmp;
	char	*path;
	char	*exit_value;
	char	*home;
	char	cwd[PATH_MAX];

	home = get_env_value("HOME", data->env);
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
			data->exit_value = handle_empty_cmd(data, data->first_cmd);
		else if (handle_heredoc_before_exec(data) == 130)
		{
			data->exit_value = 130;
			return ;
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
		free_command(&data->first_cmd);
	}
	free_args_list(&data->args_list);
	free(data->line);
}

void    print_list(t_args *head)
{
    t_args    *tail;

    printf("Liste dans l'ordre :\n");
    while (head)
    {
        printf(BLUE"%s "RESET, head->content);
        //printf(YELLOW"op_in_quote = %d "RESET, head->op_in_quote);
        printf("--> ");
        if (head->next == NULL)
            tail = head;
        head = head->next;
    }
    printf("NULL\n");
}

static void	process_line(t_data *data)
{
	if (onlyspace(data->line))
	{
		free(data->line);
		return ;
	}
	parsing_args(data, data->line);
	print_list(data->args_list);
	add_history(data->line);
	if (!validate_syntax(data, data->args_list))
	{
		free_args_list(&data->args_list);
		free_command(&data->first_cmd);
		return ;
	}
	build_and_execute(data);
}

static void	loop(t_data *data, char *prompt)
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
