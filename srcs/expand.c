/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:00:53 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/23 19:16:37 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/* static size_t	expand_arg_size(char *arg, char **env)
{
	size_t	len;
	int		i;

	len = ft_strlen(arg);
	i = 0;
	while ()
} */

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

static char	*get_env_value(char *var_name, char **env)
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

static int	handle_env_var(char *str, int *i, char *result, int j, char **env)
{
	int		start;
	char	*var_name;
	char	*var_value;
	int		var_len;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (start == *i)
	{
		result[j++] = '$';
		return (j);
	}
	var_name = ft_substr(str, start, (*i) - start);
	if (!var_name)
		return (-1);
	var_value = get_env_value(var_name, env);
	if (var_value)
	{
		var_len = ft_strlen(var_value);
		ft_memcpy(result + j, var_value, var_len);
		j += var_len;
	}
	free(var_name);
	return (j);
}

char	*expand_arg(char *arg, char **env)
{
	char	*result;
	int		i;
	int		j;
	int		len = ft_strlen(arg);

	result = malloc(sizeof(char) * (len * 4 + 1));
	if (!result)
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
				j = handle_exit_status(result, j);
				continue;
			}
			j = handle_env_var(arg, &i, result, j, env);
			if (j == -1)
			{
				free(result);
				return (NULL);
			}
		}
		else
			result[j++] = arg[i++];
	}
	result[j] = '\0';
	return (result);
}
