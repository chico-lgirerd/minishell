/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:04:00 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/16 09:29:35 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "utils.h"
#include "cmd.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

char	**dup_env(t_data *data)
{
	int		i;
	int		envlen;
	char	**new_env;
	
	envlen = envplen(data->env);
	new_env = malloc(sizeof(char *) * (envlen + 1));
	if (!new_env)
		exit(1);
	i = 0;
	while (data->env[i] != NULL)
	{
		new_env[i] = ft_strdup(data->env[i]);
		if (!new_env[i])
		{
			while (i >= 0)
			{
				free(new_env[i]);
				i--;
			}
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**copy_except(char **env, char *var)
{
	int		i;
	int		j;
	int		envlen;
	int		varlen;
	char	**new_env;

	envlen = envplen(env);
	new_env = malloc(sizeof(char *) * (envlen + 1));
	if (!new_env)
		exit(1);
	varlen = ft_strlen(var);
	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (!(ft_strncmp(env[i], var, varlen) == 0 && env[i][varlen] == '='))
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
				exit(1);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	unset(char **args, t_data *data)
{
	char	**new_env;
	
	new_env = NULL;
	if (!args[0])
		return (0);
	if (ft_strchr(args[0], '=') || !valid_var_name(args[0]))
		return (0);
	if (!data->touched_env)
	{
		new_env = dup_env(data);
		data->env = new_env;
		data->touched_env = 1;
	}
	new_env = copy_except(data->env, args[0]);
	if (!new_env)
		exit(1);
	free_chars(data->env);
	data->env = new_env;
	return (0);
}
