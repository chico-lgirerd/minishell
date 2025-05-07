/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:45:26 by tiaperei          #+#    #+#             */
/*   Updated: 2024/12/12 16:09:32 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned(unsigned int u)
{
	int	len;

	if (u > 9)
	{
		len = print_unsigned(u / 10);
		return (len + print_unsigned(u % 10));
	}
	else
		return (print_char(u + '0'));
}
