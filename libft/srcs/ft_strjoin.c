/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:18:52 by tiaperei          #+#    #+#             */
/*   Updated: 2025/05/01 12:43:19 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (ptr == NULL)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			ptr[i] = s1[i];
			i++;
		}
	}
	if (s2)
	{
		while (s2[j])
			ptr[i++] = s2[j++];
	}
	ptr[i] = '\0';
	return (ptr);
}

/* int	main(void)
{
	char	*result;
	char	*s1 = "ideebfaf";
	char	*s2 = NULL;
	
	result = ft_strjoin(s1, s2);
	printf("%s\n", result);
	free(result);
} */