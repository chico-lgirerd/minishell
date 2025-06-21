/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:55:39 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/21 16:58:45 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "utils.h"
#include "cmd.h"

void	exit_expand(t_data *data, char *sub_arg, char *tmp, char **tab)
{
	int	i;

	i = 0;
	if (data->arg)
		free(data->arg);
	if (data->expanded_arg)
		free(data->expanded_arg);
	if (tmp)
		free(tmp);
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	free(sub_arg);
	ft_error(data, "malloc: failed in expand_no_quote", 12);
}

int	print_dollar(t_data *data, int *i, int *j)
{
	data->expanded_arg[*j] = '$';
	(*j)++;
	(*i)++;
	return (*j);
}

int	find_last_expand(char *sub_arg)
{
	int	i;
	int	last_index;

	last_index = -1;
	i = 0;
	while (sub_arg[i])
	{
		if (sub_arg[i] == '$' && sub_arg[i + 1])
		{
			if (sub_arg[i + 1] == '?'
				|| ft_isalnum(sub_arg[i + 1]) || sub_arg[i + 1] == '_')
				last_index = i + 1;
		}
		i++;
	}
	return (last_index);
}

int	dup_tmp_and_free(t_data *data, char *sub_arg, char *tmp, char **tab)
{
	data->arg = ft_strdup(tmp);
	if (!data->arg)
	{
		free(tab);
		exit_expand(data, sub_arg, tmp, NULL);
	}
	free(tmp);
	tmp = NULL;
	free(tab);
	return (0);
}

int	split_expand(t_data *data, char *sub_arg, char **tab, int j)
{
	while (*tab)
	{
		if (!*(tab + 1))
		{
			if (data->last_expand)
			{
				ft_memcpy(data->expanded_arg + j, *tab, ft_strlen(*tab));
				j += ft_strlen(*tab);
				free(*tab);
				break ;
			}
			data->arg = ft_strdup(*tab);
			if (!data->arg)
			{
				free(*tab);
				free(data->original_tab);
				exit_expand(data, sub_arg, NULL, NULL);
			}
			free(*tab);
			break ;
		}
		append_node(data, &data->args_list, *tab, false);
		tab++;
	}
	return (j);
}
