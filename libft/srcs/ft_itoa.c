/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:07:08 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/24 17:00:39 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nlen(int n)
{
	int	i;

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
	int		i;
	char	*ptr;

	i = ft_nlen(n);
	ptr = malloc(sizeof(char) * ft_nlen(n) + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[i] = '\0';
	i--;
	return (is_itoa(n, i, ptr));
}
/*
int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	printf("%s\n", ft_itoa(atoi(av[1])));
	printf("%d\n", ft_nlen(atoi(av[1])));
	return (0);
}*/