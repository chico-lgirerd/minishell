/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:04:00 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/06 10:00:35 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "builtins.h"
#include "utils.h"

void	lstpop(t_env **env, char *var)
{
	t_env	*curr;
	int		varlen;

	curr = *env;
	varlen = ft_strlen(var);
	while (curr)
	{
		if (!ft_strncmp(curr->var, var, varlen) && curr->var[varlen] == '=')
		{
			if (curr->prev)
				curr->prev->next = curr->next;
			else
				*env = curr->next;
			if (curr->next)
				curr->next->prev = curr->prev;
			free(curr->var);
			free(curr);
			return ;
		}
		curr = curr->next;
	}
}

int	unset(char **args, t_data *data)
{
	if (!args[0])
		return (0);
	if (ft_strchr(args[0], '=') || !valid_var_name(args[0]))
		return (0);
	lstpop(&data->env, args[0]);
	return (0);
}
