/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:07:08 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 17:48:34 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	int_len(int n)
{
	size_t	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	i++;
	return (i);
}

char	*is_itoa(int n, int i, char *ptr)
{
	if (n == -2147483648)
	{
		ptr[i--] = '8';
		n = -214748364;
	}
	if (n < 0)
	{
		n *= -1;
		ptr[0] = '-';
	}
	if (n == 0)
		ptr[0] = '0';
	while (n > 0)
	{
		ptr[i--] = n % 10 + '0';
		n /= 10;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*ptr;

	i = int_len(n);
	ptr = malloc(sizeof(char) * (i + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[i] = '\0';
	i--;
	return (is_itoa(n, i, ptr));
}
