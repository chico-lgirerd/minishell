/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:21:48 by tiaperei          #+#    #+#             */
/*   Updated: 2024/11/08 12:25:28 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s2;
	unsigned char	c2;
	size_t			i;

	s2 = (unsigned char *)s;
	c2 = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (s2[i] == c2)
			return (s2 + i);
		i++;
	}
	return ((void *)0);
}
/*
int main() {

	char s[] = {99, 1, 2 ,3 ,4 ,5};
	const unsigned int size = 6;

	// On recherche une valeur inhéxistante :
	void * found = ft_memchr( s, 5, size );
	printf(  "%s\n", ( found != NULL ? "found" : "not found" ) );

	// On recherche une valeur existante :
	found = ft_memchr( s, 5, size );
	printf( "%s\n", ( found != NULL ? "found" : "not found" ) );
	if ( found != NULL ) {
		printf( "La valeur à la position calculée est %d\n", *((char *) found) );
	}
}*/