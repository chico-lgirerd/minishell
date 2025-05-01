/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:00:51 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/28 17:12:45 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size_s;
	char	*ptr;
	int		i;

	if (!s)
		return (NULL);
	size_s = 0;
	while (s[size_s])
		size_s++;
	ptr = malloc((size_s + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/* int	main(void)
{
	char	*dup = ft_strdup(NULL);
	printf("%s\n", dup);
	free(dup);
} */
