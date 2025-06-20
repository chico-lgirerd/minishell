/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:29:54 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 17:51:22 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	if (!s1 || !s2)
		return (-1);
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	i = 0;
	while (cs1[i] == cs2[i] && cs1[i])
		i++;
	return (cs1[i] - cs2[i]);
}
