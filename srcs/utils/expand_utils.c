/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:55:39 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 16:56:54 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_last_expand(char *sub_arg)
{
	int i;
	int	last_index;

	last_index = -1;
	i = 0;
	while (sub_arg[i])
	{
		if (sub_arg[i] == '$' && sub_arg[i + 1])
		{
			if (sub_arg[i + 1] == '?' || ft_isalnum(sub_arg[i + 1]) || sub_arg[i + 1] == '_')
				last_index = i + 1;
		}
		i++;
	}
	return (last_index);
}
