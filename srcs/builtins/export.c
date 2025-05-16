/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:34:34 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/16 13:16:54 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "cmd.h"
#include <stdlib.h>
#include "utils.h"

char	*extract_var_name(char *var, size_t *len)
{
	int		i;
	char	*var_name;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] != '=')
		return (NULL);
	var_name = malloc(i + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, var, i + 1);
	var_name[i] = '\0';
	*len = i;
	return (var_name);
}

int	replace_existing(char *var, char **envp)
{
	int		i;
	size_t	len;
	char	*var_name;

	var_name = extract_var_name(var, &len);
	if (!var_name)
		return (0);
	i = 0;
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], var, len) == 0) && (envp[i][len] == '='))
		{
			if (!check_location(envp[i]))
				free(envp[i]);
			envp[i] = ft_strdup(var);
			free(var_name);
			return (1);
		}
		i++;
	}
	free(var_name);
	return (0);
}

int	envplen(char **envp)
{
	int	i;

	if (!envp)
		return (0);
	i = 0;
	while ((envp)[i])
		i++;
	return (i);
}

int	add_new_var(t_data *data, char *var, int len_env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = malloc(sizeof(char *) * (len_env + 2));
	if (!new_env)
		return (1);
	while (i < len_env)
	{
		// new_env[i] = (data->env)[i];
		new_env[i] = ft_strdup(data->env[i]);
		i++;
	}
	new_env[len_env] = ft_strdup(var);
	if (!new_env[len_env])
		return (free(new_env), 1);
	new_env[len_env + 1] = NULL;
	data->env = new_env;
	return (0);
}

int	export(char **args, t_data *data)
{
	char	**new_env;

	if (!args[0])
		return (print_export_list(data->env));
	if (!valid_var_name(args[0]))
		return (output_id_error(args[0]));
	if (!ft_strchr(args[0], '='))
		return (0); // juste export mais pas set
	if (!data->touched_env)
	{
		new_env = dup_env(data);
		data->env = new_env;
		data->touched_env = 1;
	}
	if (replace_existing(args[0], data->env))
		return (0);
	if (add_new_var(data, args[0], envplen(data->env)) != 0)
		return (1);
	return (0);
}

