/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:34:40 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 17:51:18 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
