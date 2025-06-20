/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:55:39 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 22:51:10 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "utils.h"

int	print_dollar(t_data *data, int *i, int *j)
{
	data->expanded_arg[*j] = '$';
	(*j)++;
	(*i)++;
	return (*j);
}

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

int	handle_arg_before(t_data *data, char *sub_arg, char **tab)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = strjoin_and_free(data, data->arg, tab[i]);
	if (!tmp)
		free_and_exit(data, sub_arg, "malloc: failed in handle_arg_before");
	if (!tab[i + 1])
	{
		data->arg = ft_strdup(tmp);
		if (!data->arg)
			free_and_exit(data, sub_arg, "malloc: failed in handle_arg_before"); //free tmp, tab
		free(tmp);
		tmp = NULL;
		free(tab);
		return (0);
	}
	append_node(data, &data->args_list, tmp, false);
	i++;
	data->arg = NULL;
	tmp = NULL;
	return (1);
}
