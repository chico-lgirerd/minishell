/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:59:10 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/03 16:27:55 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing.h"
#include "builtins.h"
#include "utils.h"
#include "libft.h"
#include "colors.h"

int	update_env_var(t_data *data, char *key, char *value)
{
	char	*joined;

	joined = ft_strjoin3(key, "=", value);
	if (!joined)
	{
		ft_putendl_fd(RED"minishell: malloc: strjoin failed"RESET, 2);
		free_all_data(data, true);
		return (1);
	}
	if (!replace_existing(joined, data->env))
		if (add_new_var(data, joined) == -1)
			return (1);
	free(joined);
	return (0);
}

int	env(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		printf("%s\n", curr->var);
		curr = curr->next;
	}
	return (0);
}
