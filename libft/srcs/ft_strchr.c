/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:34:40 by tiaperei          #+#    #+#             */
/*   Updated: 2024/11/11 14:48:49 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c2;

	c2 = (unsigned char)c;
	while (*s)
	{
		if (*s == c2)
			return ((char *)s);
		s++;
	}
	if (c2 == '\0')
		return ((char *)s);
	else
		return (0);
}
/*
int	main()
{
	const char	*s = "teste";
	int		c = '\0';

	printf("%s\n", ft_strchr(s, c));
}*/