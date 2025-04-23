/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:00:53 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/18 16:49:22 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*expand_env_vars(char *str, char **env)
{
	char	*result;
	int		i;
	int		j;
	int		len = ft_strlen(str);

	result = malloc(sizeof(char) * (len * 4 + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			if (str[i] == '?')
			{
				i++;
				j = handle_exit_status(result, j);
				continue;
			}
			j = handle_env_var(str, &i, result, j, env);
			if (j == -1)
			{
				free(result);
				return (NULL);
			}
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static hanlde