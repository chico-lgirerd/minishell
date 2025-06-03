/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:34:34 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/03 16:29:15 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "cmd.h"
#include <stdlib.h>
#include "utils.h"
#include "colors.h"

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

int	replace_existing(char *var, t_env *env)
{
	size_t	len;
	char	*var_name;
	t_env	*curr;

	var_name = extract_var_name(var, &len);
	if (!var_name)
		return (0);
	curr = env;
	while (curr)
	{
		if ((ft_strncmp(curr->var, var, len) == 0) && (curr->var[len] == '='))
		{
			free(curr->var);
			curr->var = ft_strdup(var);
			free(var_name);
			return (1);
		}
		curr = curr->next;
	}
	free(var_name);
	return (0);
}

int	add_new_var(t_data *data, char *var)
{
	t_env	*newnode;
	int		i;

	i = get_env_size(data->env);
	newnode = lstnew(var, i + 1);
	if (!newnode)
	{
		ft_putendl_fd(RED"minishell: lstnew failed"RESET, 2);
		return (-1);
	}
	lstadd_back(&data->env, newnode);
	return (0);
}

int	export(char **args, t_data *data)
{
	if (!args[0])
		return (print_export_list(data->env));
	if (!valid_var_name(args[0]))
		return (output_id_error(args[0]));
	if (!ft_strchr(args[0], '='))
		return (0);
	if (replace_existing(args[0], data->env))
		return (0);
	if (add_new_var(data, args[0]) != 0)
		return (1);
	return (0);
}
