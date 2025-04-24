/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:00:30 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/24 14:31:10 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	print_escaped(char *s)
{
	while (*s)
	{
		if (*s == '"' || *s == '\\')
			printf("\\");
		pritnf("%c", *s);
		s++;
	}
}

int	print_export_list(char **envp)
{
	int		i;
	char	*eq;

	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			*eq = '\0';
			printf("export %s=\"", envp[i]);
			print_escaped(eq + 1);
			printf("\"\n");
			*eq = '=';
		}
		else
			printf("export %s\n", envp[i]);
		i++;
	}
}
