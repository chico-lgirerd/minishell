/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:00:30 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/16 12:44:11 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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

int	print_export_list(char **envp)
{
	int		i;
	char	*equal;

	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			*equal = '\0';
			printf("export %s=\"", envp[i]);
			print_escaped(equal + 1);
			printf("\"\n");
			*equal = '=';
		}
		else
			printf("export %s\n", envp[i]);
		i++;
	}
	return (0);
}
