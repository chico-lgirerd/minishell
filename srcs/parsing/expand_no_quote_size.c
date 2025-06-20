/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_quote_size.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:40:08 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 19:33:41 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "utils.h"
#include "libft.h"

/* static size_t	expand_size(t_data *data, char *var_value, char *sub_arg)
{
	int		i;
	char	**tab;
	
	i = 0;
	tab = ft_split(var_value, ' ');
	if (!tab)
		free_and_exit(data, sub_arg, "malloc: failed in expand_size");
	while (tab[i])
	{
		if (!(tab[i + 1]))
		{
			if (data->last_expand)
			{
				size = ft_strlen(tab[i])
				break ;
			}
			
		}
		i++;
	}
	free(tab);
	return (size);
}
 */
static size_t	env_var_size(t_data *data, char *sub_arg, int *i)
{
	size_t	size;
	int		start;
	char	*var_name;
	char	*var_value;

	size = 0;
	start = *i;
	while (sub_arg[*i] && (ft_isalnum(sub_arg[*i]) || sub_arg[*i] == '_'))
		(*i)++;
	if (start == *i)
		return (1);
	var_name = ft_substr(sub_arg, start, (*i) - start);
	if (!var_name)
		free_and_exit(data, sub_arg, "malloc: failed in env_var_size");
	var_value = get_env_value(var_name, data->env);
	if (var_value)
		size = expand_size(data, var_value, sub_arg);
	free(var_name);
	return (size);
}

static size_t	exit_value_size(t_data *data, int *i)
{
	size_t	size;

	(*i)++;
	if (g_signal)
		size = int_len(g_signal + 128);
	else
		size = int_len(data->exit_value);
	
	return (size);
}

size_t	expanded_arg_size_no_quote(t_data *data, char *sub_arg)
{
	size_t	size;
	int		i;
	int		last;

	size = 0;
	i = 0;
	if (!sub_arg)
		return (0);
	last = find_last_expand(sub_arg);
	while (sub_arg[i])
	{
		if (sub_arg[i] == '$' && sub_arg[i + 1])
		{
			i++;
			if (sub_arg[i] == '?')
				size += exit_value_size(data, &i);
			else
				size += env_var_size(data, sub_arg, &i);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}
