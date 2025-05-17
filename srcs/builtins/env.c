/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:59:10 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/17 18:16:31 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing.h"

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
