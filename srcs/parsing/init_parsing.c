/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:45:31 by tiaperei          #+#    #+#             */
/*   Updated: 2025/05/13 14:30:30 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "colors.h"
#include "colors.h"
#include "libft.h"

void	init_data(t_data *data, char **env)
{
	data->env = env;
	data->line = NULL;
	data->quote = 0;
	data->expanded_arg = NULL;
	data->args_list = NULL;
	data->first_cmd = NULL;
	data->touched_env = 0;
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
	ft_memset(cmd, 0, sizeof(t_command));
	return (cmd);
}
