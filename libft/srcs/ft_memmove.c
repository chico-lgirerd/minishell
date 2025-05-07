/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:22:36 by tiaperei          #+#    #+#             */
/*   Updated: 2024/11/12 16:50:09 by tiaperei         ###   ########.fr       */
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
/*
#include <stdlib.h>
#include <string.h>

int	main()
{
	char	dest[] = "";
	char	src[] = "abcdef";
	size_t	n = sizeof(char) * 3;

	ft_memmove(dest, src, n);
	for (n = 0; n < 3; n++)
		printf("%c ", dest[n]);
}*/
