/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:00:53 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/21 16:12:59 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"
#include "utils.h"

static void	free_and_exit(t_data *data, char *sub_arg, char *str)
{
	if (data->arg)
		free(data->arg);
	if (data->expanded_arg)
		free(data->expanded_arg);
	free(sub_arg);
	ft_error(data, str, 12);
}

static int	handle_exit_status(t_data *data, char *sub_arg, int j)
{
	char	*exit_str;
	int		exit_len;

	exit_str = NULL;
	if (g_signal)
	{
		exit_str = ft_itoa(g_signal + 128);
		g_signal = 0;
	}
	else
		exit_str = ft_itoa(data->exit_value);
	if (!exit_str)
		free_and_exit(data, sub_arg, "malloc: failed in handle_exit_status");
	exit_len = ft_strlen(exit_str);
	ft_memcpy(data->expanded_arg + j, exit_str, exit_len);
	j += exit_len;
	free(exit_str);
	return (j);
}

static int	handle_env_var(t_data *data, char *sub_arg, int *i, int j)
{
	int		start;
	char	*var_name;
	char	*var_value;
	int		var_len;

	start = *i;
	while (sub_arg[*i] && (ft_isalnum(sub_arg[*i]) || sub_arg[*i] == '_'))
		(*i)++;
	if (start == *i)
	{
		data->expanded_arg[j++] = '$';
		return (j);
	}
	var_name = ft_substr(sub_arg, start, (*i) - start);
	if (!var_name)
		free_and_exit(data, sub_arg, "malloc: failed in handle_env_var");
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

char	*get_env_value(char *var_name, t_env *env)
{
	int		var_len;
	t_env	*curr;

	var_len = ft_strlen(var_name);
	curr = env;
	while (curr)
	{
		if (ft_strncmp(curr->var, var_name, var_len) == 0
			&& curr->var[var_len] == '=')
			return (curr->var + var_len + 1);
		curr = curr->next;
	}
	if (ft_strcmp(var_name, "HOME") == 0)
		return ("NOHOME");
	return (NULL);
}

void	expand_arg(t_data *data, char *sub_arg)
{
	int		i;
	int		j;

	data->expanded_arg = malloc(expanded_arg_size(data, sub_arg) + 1);
	if (!data->expanded_arg)
		free_and_exit(data, sub_arg, "malloc: failed in expand_arg");
	i = 0;
	j = 0;
	while (sub_arg[i])
	{
		if (sub_arg[i] == '$' && sub_arg[i + 1] && ++i)
		{
			if (sub_arg[i] == '?' && ++i)
			{
				j = handle_exit_status(data, sub_arg, j);
				continue ;
			}
			j = handle_env_var(data, sub_arg, &i, j);
		}
		else
			data->expanded_arg[j++] = sub_arg[i++];
	}
	data->expanded_arg[j] = '\0';
}
