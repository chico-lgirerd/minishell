/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:28:47 by tiaperei          #+#    #+#             */
/*   Updated: 2024/11/12 15:14:58 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[j] && j < size)
		j++;
	if (size == j)
		return (size + ft_strlen(src));
	while (src[i] && j + i < size - 1)
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (j + ft_strlen(src));
}
/*
int	main(void)
{
	char	dst[] = "0";
	char	src[] = "456789";

	printf("%zu \n", ft_strlcat(dst, src, 4));
	return (0);
}*/
