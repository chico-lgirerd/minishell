/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:45:31 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/15 20:41:47 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "color.h"

void	init_data(t_data *data)
{
	data->line = NULL;
	data->args_list = NULL;
	init_args(data->args_list);
}

void	init_args(t_args_list *args)
{
	args->content = NULL;
	args->in_quote = 0;
	args->next = NULL;
	args->prev = NULL;
}

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
	cmd->append_output = NULL;
	cmd->heredoc_delimiter = NULL;
	cmd->next = NULL;
	return (cmd);
}
