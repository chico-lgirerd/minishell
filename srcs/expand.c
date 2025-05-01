/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:00:53 by tiaperei          #+#    #+#             */
/*   Updated: 2025/05/01 17:30:01 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"
#include "colors.h"

static void	free_arg(char *arg1, char *arg2, char *str)
{
	if (arg1)
		free(arg1);
	if (arg2)
		free(arg2);
	printf(RED"Error : malloc in %s.\n"RESET, str);
	exit(EXIT_FAILURE);
}

static int	handle_exit_status(t_data *data, char *arg, int j)
{
	char	*exit_str;
	int		exit_len;

	(void)arg;
	exit_str = ft_itoa(g_exit_value);
	if (!exit_str)
		free_arg(data->expanded_arg, arg, "handle_exit_status failed");
	exit_len = ft_strlen(exit_str);
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
	var_name = ft_substr(arg, start, (*i) - start);
	if (!var_name)
		free_arg(data->expanded_arg, arg, "handle_env_var failed");
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

char	*get_env_value(char *var_name, char **env)
{
	int	var_len;
	int	i;

	var_len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, var_len) == 0
			&& env[i][var_len] == '=')
			return (env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}

void	expand_arg(t_data *data, char *arg)
{
	int		i;
	int		j;

	data->expanded_arg = malloc(expanded_arg_size(arg, data->env) + 1);
	if (!data->expanded_arg || !arg)
		free_arg(data->expanded_arg, arg, "expand_arg failed");
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] && ++i)
		{
			if (arg[i] == '?' && ++i)
			{
				j = handle_exit_status(data, arg, j);
				continue ;
			}
			j = handle_env_var(data, arg, &i, j);
		}
		else
			data->expanded_arg[j++] = arg[i++];
	}
	data->expanded_arg[j] = '\0';
}
