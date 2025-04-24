/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:00:53 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/24 17:05:41 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"

static int	handle_exit_status(char *result, int j)
{
	char	*exit_str;
	int		exit_len;

	exit_str = ft_itoa(g_exit_value);
	if (!exit_str)
		return (-1);
	exit_len = ft_strlen(exit_str);
	ft_memcpy(result + j, exit_str, exit_len);
	j += exit_len;
	free(exit_str);
	return (j);
}

static int	handle_env_var(t_data *data, char *arg, int *i, int j)
{
	int		start;
	char	*var_name;
	char	*var_value;
	int		var_len;

	start = *i;
	while (arg[*i] && (ft_isalnum(arg[*i]) || arg[*i] == '_'))
		(*i)++;
	if (start == *i)
	{
		data->expanded_arg[j++] = '$';
		return (j);
	}
	var_name = ft_substr(arg, start, (*i) - start);
	if (!var_name)
		return (-1);
	var_value = get_env_value(var_name, data->env);
	if (var_value)
	{
		var_len = ft_strlen(var_value);
		ft_memcpy(data->expanded_arg + j, var_value, var_len);
		j += var_len;
	}
	free(var_name);
	return (j);
}

char	*expand_arg(t_data *data, char *arg)
{
	int		i;
	int		j;

	data->expanded_arg = malloc(sizeof(char) * (expand_arg_size(arg, data->env) + 1));
	if (!data->expanded_arg)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1])
		{
			i++;
			if (arg[i] == '?')
			{
				i++;
				j = handle_exit_status(data->expanded_arg, j);
				continue ;
			}
			j = handle_env_var(data, arg, &i, j);
			if (j == -1)
			{
				free(data->expanded_arg);
				return (NULL);
			}
		}
		else
			data->expanded_arg[j++] = arg[i++];
	}
	data->expanded_arg[j] = '\0';
	return (data->expanded_arg);
}
