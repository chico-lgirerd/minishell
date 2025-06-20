/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:53:49 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 17:46:47 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	check_overflow(unsigned long long nb)
{
	if (nb > 9223372036854775807)
		return (1);
	else
		return (0);
}

int	res_overflow(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int					i;
	int					sign;
	unsigned long long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == 32)
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i + 1] == '-' || nptr[i + 1] == '+')
			return (0);
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
		if (check_overflow(nb))
			return (res_overflow(sign));
	}
	return (nb * sign);
}
