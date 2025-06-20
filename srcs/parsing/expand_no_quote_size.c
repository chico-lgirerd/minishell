/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_quote_size.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:40:08 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 22:03:01 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "utils.h"
#include "libft.h"

static size_t	expand_size(t_data *data, char *var_value,
	char *sub_arg, size_t *size)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split(var_value, ' ');
	if (!tab)
		free_and_exit(data, sub_arg, "malloc: failed in expand_size");
	while (tab[i])
	{
		if (!(tab[i + 1]) && data->last_expand)
		{
			*size += ft_strlen(tab[i]);
			free(tab[i]);
			break ;
		}
		*size = 0;
		free(tab[i]);
		i++;
	}
	free(tab);
	return (*size);
}

static size_t	env_var_size(t_data *data, char *sub_arg, int *i, size_t *size)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *i;
	while (sub_arg[*i] && (ft_isalnum(sub_arg[*i]) || sub_arg[*i] == '_'))
		(*i)++;
	if (start == *i)
		return (++(*size));
	var_name = ft_substr(sub_arg, start, (*i) - start);
	if (!var_name)
		free_and_exit(data, sub_arg, "malloc: failed in env_var_size");
	var_value = get_env_value(var_name, data->env);
	if (var_value)
		expand_size(data, var_value, sub_arg, size);
	free(var_name);
	return (*size);
}

static size_t	exit_value_size(t_data *data, int *i, size_t *size)
{
	(*i)++;
	if (g_signal)
		*size = int_len(g_signal + 128);
	else
		*size = int_len(data->exit_value);
	return (*size);
}

size_t	expanded_arg_size_no_quote(t_data *data, char *sub_arg)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	data->last_pos = find_last_expand(sub_arg);
	data->last_expand = false;
	while (sub_arg[i])
	{
		if (sub_arg[i] == '$' && sub_arg[i + 1] && ++i)
		{
			if (data->last_pos == i)
				data->last_expand = true;
			if (sub_arg[i] == '?')
				exit_value_size(data, &i, &size);
			else
				env_var_size(data, sub_arg, &i, &size);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}
