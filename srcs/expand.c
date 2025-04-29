/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:00:53 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/28 21:52:45 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"
#include "utils.h"

//static void	free_expand

static int	handle_exit_status(t_data *data, char *arg, int j)
{
	char	*exit_str;
	int		exit_len;

	exit_str = ft_itoa(g_exit_value);
	if (!exit_str)
	{
		free(arg);
		free(data->expanded_arg);
		ft_error(data, "malloc in handle_exit_status failed");
	}
	exit_len = ft_strlen(exit_str);
	//protection
	ft_memcpy(data->expanded_arg + j, exit_str, exit_len);
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
	//var_name = ft_substr(arg, start, (*i) - start);
	var_name = NULL;
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
	if (!data->expanded_arg || !arg)
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
				j = handle_exit_status(data, arg, j);
				continue ;
			}
			j = handle_env_var(data, arg, &i, j);
			if (j == -1)
			{
				printf("TTTTTTTTTTTTTTTTTTTTTTTTT\n");
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
