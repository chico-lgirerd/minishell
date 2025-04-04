/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:04:00 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/04 12:20:51 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include <stdlib.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>

void	unset_var(char *var, char ***envp, size_t len_var)
{
	int		i;
	int		j;
	char	**new_env;
	int		len_env;
	
	len_env = envplen(*envp);
	new_env = malloc(sizeof(char *) * (len_env + 1));
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], var, len_var) == 0)
			;
		else
		{
			new_env[j] = (*envp)[i];
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	*envp = new_env;
}

void	unset(char	*input, char ***envp)
{
	if (!input)
		return ;
	if (ft_strchr(input, '='))
		return ;
	unset_var(input, envp, ft_strlen(input));
}
