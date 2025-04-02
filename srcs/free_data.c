/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:45:28 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/02 18:20:14 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_all_data(t_data *data)
{
	if (data->args_list)
		free_args_list(&(data->args_list));
}

void	free_args_list(t_args_list **args_list)
{
	t_args_list	*tmp;
	t_args_list	*current;

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