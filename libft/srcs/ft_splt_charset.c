/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splt_charset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:07:34 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/21 15:41:54 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_words(char const *s, char *charset, int i)
{
	int	len;

	len = 0;
	while (!in_charset(s[i], charset) && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

static char	*put_words(char const *s, char *charset, int *i)
{
	int		j;
	int		size;
	char	*str;

	size = len_words(s, charset, *i);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	j = 0;
	while (!in_charset(s[*i], charset) && s[*i])
	{
		str[j] = s[*i];
		j++;
		(*i)++;
	}
	str[j] = '\0';
	return (str);
}

static char	**free_all(char **strs, int j)
{
	while (j > 0)
	{
		free(strs[j - 1]);
		j--;
	}
	free(strs);
	return (NULL);
}

char	**ft_split_charset(char const *s, char *charset)
{
	int		i;
	int		j;
	char	**strs;

	i = 0;
	j = 0;
	strs = malloc(sizeof(char *) * (count_words_charset(s, charset) + 1));
	if (strs == NULL)
		return (NULL);
	while (s[i])
	{
		if (!in_charset(s[i], charset))
		{
			strs[j] = put_words(s, charset, &i);
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
