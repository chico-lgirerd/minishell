/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:22:36 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 17:49:53 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest2;
	unsigned char	*src2;

	dest2 = (unsigned char *)dest;
	src2 = (unsigned char *)src;
	i = 0;
	if (dest2 > src2 && src2 + n > dest2)
	{
		while (n-- > 0)
		{
			dest2[n] = src2[n];
		}
	}
	else
	{
		while (i < n)
		{
			dest2[i] = src2[i];
			i++;
		}
	}
	return (dest2);
}
