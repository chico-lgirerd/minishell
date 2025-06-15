/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:22:02 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/15 16:24:38 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, char *src)
{
	char	*res;
	int		i;
	int		j;

	if (!src)
		return (dst);
	res = malloc(ft_strlen(dst) + ft_strlen(src) + 1);
	i = 0;
	while (dst[i])
	{
		res[i] = dst[i];
		i++;
	}
	j = 0;
	while (src[i])
	{
		res[i] = src[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}
