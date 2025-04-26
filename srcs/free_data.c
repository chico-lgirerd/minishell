/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:45:28 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/26 17:23:08 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

void	free_all_data(t_data *data)
{
	if (data->args_list)
		free_args_list(&(data->args_list));
}

void	free_args_list(t_args **args_list)
{
	t_args	*tmp;
	t_args	*current;

	if (!args_list || !(*args_list))
		return ;
	current = *args_list;
	while (current)
	{
		tmp = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = tmp;
	}
	*args_list = NULL;
}

void	free_command(t_command **first_cmd)
{
	t_command	*tmp;
	t_command	*current;
	int			i;

	if (!first_cmd || !(*first_cmd))
		return ;
	current = *first_cmd;
	while (current)
	{
		tmp = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				free(current->args[i]);
				i++;
			}
			free(current->args);
		}
		if (current->input_file)
			free(current->input_file);
		if (current->output_file)
			free(current->output_file);
		if (current->heredoc_delimiter)
			free(current->heredoc_delimiter);
		free(current);
		current = tmp;
	}
	*first_cmd = NULL;
}
