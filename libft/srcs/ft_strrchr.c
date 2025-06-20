/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:58:36 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 17:52:24 by lgirerd          ###   ########lyon.fr   */
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
