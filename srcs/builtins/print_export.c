/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:00:30 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/13 15:07:07 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

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

static void	swap_env(t_env **a, t_env **b)
{
	t_env	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	bubble_sort_vars(t_env **env, int n)
{
	int	i;
	int	j;
	int	swapped;

	if (n <= 1)
		return ;
	i = 0;
	while (i < n - 1)
	{
		swapped = 0;
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(env[j]->var, env[j + 1]->var) > 0)
			{
				swap_env(&env[j], &env[j + 1]);
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
	}
}

static void	print_var(t_env *env_var)
{
	char	*equal;

	// if (env_var->var[0] != '_')
	// {
		equal = ft_strchr(env_var->var, '=');
		if (equal)
		{
			*equal = '\0';
			printf("export %s=\"", env_var->var);
			print_escaped(equal + 1);
			printf("\"\n");
			*equal = '=';
		}
		else
			printf("export %s\n", env_var->var);
	// }
}

static int	get_export_size(t_env *env)
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

static void	fill_env(t_env *env, t_env **new_env)
{
	int		i;
	t_env	*curr;

	i = 0;
	curr = env;
	while (curr)
	{
		new_env[i] = curr;
		i++;
		curr = curr->next;
	}
}

int	print_export_list(t_env *env)
{
	t_env	**sorted_env;
	int		size;
	int		i;

	size = get_export_size(env);
	if (size == 0)
		return (0);
	sorted_env = malloc(sizeof(t_env *) * size);
	if (!sorted_env)
		return (1);
	fill_env(env, sorted_env);
	bubble_sort_vars(sorted_env, size);
	i = 0;
	while (i < size)
	{
		print_var(sorted_env[i]);
		i++;
	}
	free(sorted_env);
	return (0);
}
