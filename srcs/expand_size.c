/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:36:20 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/24 14:59:49 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "utils.h"

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

static size_t	env_var_size(char *arg, int *i, char **env)
{
	size_t	size;
	int		start;
	char	*var_name;
	char	*var_value;

	size = 0;
	start = *i;
	while (arg[*i] && (ft_isalnum(arg[*i]) || arg[*i] == '_'))
		(*i)++;
	if (start == *i)
		return (1);
	var_name = ft_substr(arg, start, (*i) - start);
	if (!var_name)
		return (0);
	var_value = get_env_value(var_name, env);
	if (var_value)
		size = ft_strlen(var_value);
	free(var_name);
	return (size);
}

size_t	expand_arg_size(char *arg, char **env)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1])
		{
			i++;
			if (arg[i] == '?')
			{
				size += int_len(g_exit_value);
				i++;
				continue ;
			}
			size += env_var_size(arg, &i, env);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}
