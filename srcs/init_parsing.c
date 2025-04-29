/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:45:31 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/29 14:36:30 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "colors.h"

void	init_data(t_data *data, char **env)
{
	data->env = env;
	data->line = NULL;
	data->expanded_arg = NULL;
	data->args_list = NULL;
	data->first_cmd = NULL;
}

/* void	init_args(t_args *args)
{
	args->content = NULL;
	args->in_quote = 0;
	args->next = NULL;
	args->prev = NULL;
} */

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->count_args = 0;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->heredoc_delimiter = NULL;
	cmd->append_output = 0;
	cmd->next = NULL;
	return (cmd);
}
