/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:34:34 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/26 16:04:15 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include <stdlib.h>

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

int	add_new_var(char ***envp, char *var, int len_env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = malloc(sizeof(char *) * (len_env + 2));
	if (!new_env)
		return (1);
	while (i < len_env)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[len_env] = ft_strdup(var);
	if (!new_env[len_env])
		return (free(new_env), 1);
	new_env[len_env + 1] = NULL;
	*envp = new_env;
	return (0);
}

int	export(char **args, char ***envp)
{
	char	*var;

	if (!args[0])
		return (print_export_list(*envp));
	if (!ft_strchr(args[0], '='))
		return (1);
	var = ft_strdup(args[0]);
	if (!var)
		return (1);
	if (replace_existing(var, *envp))
	{
		free(var);
		return (0);
	}
	if (add_new_var(envp, var, envplen(*envp)) != 0)
	{
		free(var);
		return (1);
	}
	free(var);
	return (0);
}
