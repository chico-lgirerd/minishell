/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:17:02 by lgirerd           #+#    #+#             */
/*   Updated: 2025/03/31 14:22:30 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_chars(char **chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		free(chars[i]);
		i++;
	}
	free(chars);
}

int	return_free(char *str, char **sstr, int code)
{
	if (str)
		free(str);
	if (sstr)
		free_chars(sstr);
	return (code);
}
