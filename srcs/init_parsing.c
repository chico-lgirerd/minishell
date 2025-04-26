/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:45:31 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/26 15:38:16 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "color.h"
#include "libft.h"

void	init_data(t_data *data)
{
	data->line = NULL;
	data->args_list = NULL;
}

void	init_args(t_args *args)
{
	args->content = NULL;
	args->in_quote = 0;
	args->first_cmd = NULL;
	args->next = NULL;
	args->prev = NULL;
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	return (cmd);
}
