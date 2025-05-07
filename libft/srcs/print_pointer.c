/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:26:30 by tiaperei          #+#    #+#             */
/*   Updated: 2024/12/12 18:16:42 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer(unsigned long p)
{
	int		len;
	char	*base;

	base = "0123456789abcdef";
	if (p == 0)
		return (print_string("(nil)"));
	print_string("0x");
	if (p >= (unsigned long)ft_strlen(base))
	{
		len = print_number(p / (unsigned long)ft_strlen(base), base);
		len += print_number(p % (unsigned long)ft_strlen(base), base) + 2;
		return (len);
	}
	else
		return (print_char(base[p]) + 2);
}
