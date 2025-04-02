/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:04:00 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/02 18:41:16 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include <stdlib.h>

void	unset_var(char *var, char ***envp, size_t len)
{
	int		i;
	int		j;
	char	**new_env;
	int		len_env;

	len_env = envplen(envp);
	new_env = malloc(sizeof(char *) * (len_env + 1));
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			free(envp[i]);
		else
		{
			new_env[j] = envp[i];
			j++;
		}
		i++;
	}
	new_env[i] = NULL;
	*envp = new_env;
}

void	unset(char	*input, char ***envp)
{
	char	*var;

	while (*input && *input != '=')
		input++;
	if (!*input)
		return ;
	if (ft_strchr(input, '='))
		return ;
	var = ft_strdup(input);
	if (!var)
		return ;
	unset_var(var, envp, ft_strlen(var));
	free(var);
}
