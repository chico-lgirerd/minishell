/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:36:20 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/18 20:00:23 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "utils.h"
#include "libft.h"

static void	free_and_exit(t_data *data, char *sub_arg, char *str)
{
	if (data->arg)
		free(data->arg);
	free(sub_arg);
	ft_error(data, str, 12);
}

static void	expand_no_quote_size(t_data *data, char *sub_arg, char *var_value, size_t *size)
{
	char	**tab;
	int		i;

	tab = ft_split(var_value, ' ');
	if (!tab)
		free_and_exit(data, sub_arg, "malloc: failed in env_var_size");
	i = 0;
	if (!tab[i + 1])
		*size = ft_strlen(tab[i]);
	else
	{
		while (tab[i])
			i++;
		*size = ft_strlen(tab[i - 1]);
	}
}

static void	expand_size(t_data *data, char *sub_arg, int *i, size_t *size)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *i;
	while (sub_arg[*i] && (ft_isalnum(sub_arg[*i]) || sub_arg[*i] == '_'))
		(*i)++;
	if (start == *i)
	{
		(*size)++;
		return ;
	}
	var_name = ft_substr(sub_arg, start, (*i) - start);
	if (!var_name)
		free_and_exit(data, sub_arg, "malloc: failed in env_var_size");
	var_value = get_env_value(var_name, data->env);
	if (var_value)
	{
		if (data->quote == 0)
			expand_no_quote_size(data, sub_arg, var_value, size);
		else
			*size = ft_strlen(var_value);
	}
	free(var_name);
}

static size_t	exit_value_size(t_data *data, int *i)
{
	size_t	size;

	if (g_signal)
		size = int_len(g_signal + 128);
	else
		size = int_len(data->exit_value);
	(*i)++;
	return (size);
}

size_t	expanded_arg_size(t_data *data, char *arg)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1])
		{
			i++;
			if (arg[i] == '?')
				size += exit_value_size(data, &i);
			else
				expand_size(data, arg, &i, &size);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}
