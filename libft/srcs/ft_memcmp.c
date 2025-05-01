/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:00:54 by tiaperei          #+#    #+#             */
/*   Updated: 2024/11/11 13:59:58 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (*cs1 == *cs2 && n-- > 1)
	{
		cs1++;
		cs2++;
	}
	return (*cs1 - *cs2);
}
/*
int	main()
{
	printf("%d\n", ft_memcmp("zyxbcdefgh", "abcdefgxyz", 0));
}*/