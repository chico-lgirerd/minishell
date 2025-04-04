/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:56:01 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/04 14:25:20 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <stdlib.h>

void	ft_echo(char *input, int n)
{
	char	*var;

	while (*input)
	{
		if (*input == '$' && getenv(input + 1))
		{
			var = getenv(input + 1);
			printf("%s", var);
			input += ft_strlen(var);
		}
		else
		{
			printf("%c", *input);
			input++;
		}
	}
	if (!n)
		printf("\n");
}
