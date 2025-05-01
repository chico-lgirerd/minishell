/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:09:48 by tiaperei          #+#    #+#             */
/*   Updated: 2024/12/12 18:40:56 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_format(char c, va_list arg)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = print_char(va_arg(arg, int));
	if (c == 's')
		len = print_string(va_arg(arg, char *));
	if (c == 'p')
		len = print_pointer(va_arg(arg, unsigned long));
	if (c == 'd' || c == 'i')
		len = print_number(va_arg(arg, int), "0123456789");
	if (c == 'u')
		len = print_unsigned(va_arg(arg, unsigned int));
	if (c == 'x')
		len = print_number(va_arg(arg, unsigned int), "0123456789abcdef");
	if (c == 'X')
		len = print_number(va_arg(arg, unsigned int), "0123456789ABCDEF");
	if (c == '%')
		len = print_char('%');
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	int		i;
	va_list	arg;

	if (format == NULL)
		return (-1);
	va_start(arg, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		while (format[i] != '%' && format[i])
		{
			write(1, &format[i], 1);
			i++;
			len++;
		}
		if (format[i] == '\0')
			break ;
		i++;
		len += ft_printf_format(format[i++], arg);
	}
	va_end(arg);
	return (len);
}

/* #include <stdio.h>
int	main(void)
{
	int count;
	void *test = NULL;
	count = printf("printf : %d %x %p %%%%\n", -1, -1, test);
	printf("printf_value : %d\n", count);
	ft_printf("%c", '\n');
	count = ft_printf("ft_printf : %d %x %p %%%%\n", -1, -1, test);
	ft_printf("ft_printf_value : %d\n", count - 3);
} */
