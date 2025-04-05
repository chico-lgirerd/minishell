/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:45:31 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/05 14:24:05 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "color.h"

void	init_data(t_data *data)
{
	data->line = NULL;
	data->args_list = NULL;
	/* data->args_list = malloc(sizeof(t_args_list));
	if (!data->args_list)
		perror(RED"malloc in init_data failed"RESET); */
	//init_args(data->args_list);
}

void	init_args(t_args_list *args)
{
	args->content = NULL;
	args->in_quote = NULL;
	args->next = NULL;
	args->prev = NULL;
}