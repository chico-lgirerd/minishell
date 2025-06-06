/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:00:30 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/06 09:55:53 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

int	print_export_list(t_env *env)
{
	char	*equal;
	t_env	*curr;

	curr = env;
	while (curr)
	{
		equal = ft_strchr(curr->var, '=');
		if (equal)
		{
			*equal = '\0';
			printf("export %s=\"", curr->var);
			print_escaped(equal + 1);
			printf("\"\n");
			*equal = '=';
		}
		else
			printf("export %s\n", curr->var);
		curr = curr->next;
	}
	return (0);
}
