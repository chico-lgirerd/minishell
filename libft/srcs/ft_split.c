/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:07:34 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 17:51:02 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[i] != c && s[i])
		count++;
	while (s[i])
	{
		while (s[i] == c)
		{
			if (s[i + 1] != c && s[i + 1] != '\0')
				count++;
			i++;
		}
		i++;
	}
	return (count);
}

int	len_words(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	*put_words(char const *s, char c, int *i)
{
	int		j;
	int		size;
	char	*str;

	size = len_words(s, c, *i);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	j = 0;
	while (s[*i] != c && s[*i])
	{
		str[j] = s[*i];
		j++;
		(*i)++;
	}
	str[j] = '\0';
	return (str);
}

char	**free_all(char **strs, int j)
{
	while (j > 0)
	{
		free(strs[j - 1]);
		j--;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**strs;

	i = 0;
	j = 0;
	strs = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (strs == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			strs[j] = put_words(s, c, &i);
			if (!strs[j])
				return (free_all(strs, j));
			j++;
			if (s[i] == '\0')
				break ;
		}
		i++;
	}
	strs[j] = (void *)0;
	return (strs);
}
