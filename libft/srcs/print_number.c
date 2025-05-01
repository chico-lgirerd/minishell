/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:17:36 by tiaperei          #+#    #+#             */
/*   Updated: 2024/12/12 16:09:18 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_number(long n, char *base)
{
	int		len;

	if (n < 0)
	{
		print_char('-');
		return (print_number(-n, base) + 1);
	}
	else if (n >= (long)ft_strlen(base))
	{
		len = print_number(n / (long)ft_strlen(base), base);
		return (len + print_number(n % (long)ft_strlen(base), base));
	}
	else
		return (print_char(base[n]));
}
