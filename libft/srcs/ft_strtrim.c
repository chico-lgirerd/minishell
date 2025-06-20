/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:48:43 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 17:52:34 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_findocc(char const s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		else
			i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*ptr;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_findocc(s1[start], set) && start < end)
		start++;
	while (ft_findocc(s1[end], set) && end >= start)
		end--;
	ptr = malloc(sizeof(char) * (end - start + 2));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		ptr[i] = s1[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}
