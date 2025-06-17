/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:04:00 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/17 18:40:01 by lgirerd          ###   ########lyon.fr   */
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
		if (!ft_strncmp(curr->var, var, varlen) && (
				curr->var[varlen] == '=' || curr->var[varlen] == '\0'))
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
	int	i;

	if (!args[0])
		return (0);
	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '=') || !valid_var_name(args[i]))
			return (0);
		lstpop(&data->env, args[i]);
		i++;
	}
	return (0);
}
