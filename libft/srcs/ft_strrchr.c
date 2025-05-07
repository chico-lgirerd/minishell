/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:58:36 by tiaperei          #+#    #+#             */
/*   Updated: 2024/11/12 12:34:25 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*last_occ;
	unsigned char	c2;

	last_occ = NULL;
	c2 = (unsigned char)c;
	while (*s)
	{
		if (*s == c2)
			last_occ = s;
		s++;
	}
	if (c2 == '\0')
		return ((char *)s);
	return ((char *)last_occ);
}
/*
int	main()
{
	const char	*s = "teste";
	int		c = 'e';

	printf("%s\n", ft_strrchr(s, c));
}*/