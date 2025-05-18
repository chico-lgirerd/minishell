/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:59:10 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/18 18:11:13 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing.h"
#include "builtins.h"
#include "utils.h"

void	update_env_var(t_data *data, char *key, char *value)
{
	char	*joined;
	
	joined = ft_strjoin3(key, "=", value);
	if (!joined)
		exit(1);
	if (!replace_existing(joined, data->env))
		add_new_var(data, joined);
	free(joined);
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
