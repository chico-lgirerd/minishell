/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:52:10 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/29 13:54:01 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest2;
	const char	*src2;

	dest2 = (char *)dest;
	src2 = (const char *)src;
	i = 0;
	while (i < n)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest2);
}

/* #include <stdlib.h>

int	main()
{
	int	*dest = NULL;
	int	src[] = {54, 85, 20};
	size_t	n = sizeof(int) * 3;

	dest = (int *)malloc(n);
	ft_memcpy(dest, src, n);
	for(n = 0; n < 4; n++)
		printf("%d \n", dest[n]);
	free(dest);
} */
