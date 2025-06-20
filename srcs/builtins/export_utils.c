/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:02:36 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/20 19:43:41 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "colors.h"
#include "builtins.h"
#include "parsing.h"
#include <stdio.h>

int	output_id_error(char *arg)
{
	ft_putstr_fd(RED"minishell: export: "RESET, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return (1);
}

int	valid_var_name(char *var)
{
	int	i;

	if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (0);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	get_export_size(t_env *env)
{
	int		i;
	t_env	*curr;

	i = 0;
	curr = env;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

void	print_escaped(char *s)
{
	while (*s)
	{
		if (*s == '"' || *s == '\\')
			printf("\\");
		printf("%c", *s);
		s++;
	}
}

void	swap_env(t_env **a, t_env **b)
{
	t_env	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
