/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:03:06 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/05 12:04:28 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"

int	is_separator(const char c, char *charset)
{
	int	i;

	if (charset[0] == '\0')
		return (0);
	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_words(char const *s, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!is_separator(s[i], charset))
		count++;
	while (s[i])
	{
		if (is_separator(s[i], charset)
			&& s[i+1] && !is_separator(s[i+1], charset))
			count++;
		i++;
	}
	return (count);
}

char	*put_words(char const *s, char *charset, int *i)
{
	int		j;
	int		len;
	char	*str;

	len = 0;
	while (s[*i] && !is_separator(s[*i], charset))
	{
		len++;
		(*i)++;
	}
	*i = *i - len;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (s[*i] && !is_separator(s[*i], charset))
	{
		str[j] = s[*i];
		j++;
		(*i)++;
	}
	str[j] = '\0';
	return (str);
}

char	**free_split(char **split_str, int j)
{
	while (j > 0)
	{
		free(split_str[j - 1]);
		j--;
	}
	free(split_str);
	return (NULL);
}

char	**split(char const *s, char *charset)
{
	int		i;
	int		j;
	char	**split_str;

	if (!s || !charset || s[0] == '\0' || charset[0] == '\0')
		return (NULL);
	split_str = malloc(sizeof(char *) * (count_words(s, charset) + 1));
	if (!split_str)
		return (NULL);
	j = 0;
	i = -1;
	while (s[++i])
	{
		if (!is_separator(s[i], charset))
		{
			split_str[j] = put_words(s, charset, &i);
			if (!split_str[j])
				return (free_split(split_str, j));
			j++;
			if (s[i] == '\0')
				break ;
		}
	}
	split_str[j] = (void *)0;
	return (split_str);
}

/* int	main(int ac, char **av)
{
	int	i = 0;
	int	j = 0;
	char	**split_str;

	(void)av;
	if (ac != 1)
		return (1);
	split_str = split("ls 	-la | wc -l	;;   ", " \f\n\r\t\v");
	if (!split_str)
		return (1);
	for (i = 0; split_str[i]; i++)
	{
		printf("%s\n", split_str[i]);
		free(split_str[i]);
	}
	printf("%s\n", split_str[i]);
	free(split_str);
	printf("%d\n", count_words("ls 	-la | wc -l	;;   ", ""));
	printf("%s\n", put_words("ls 	-la | wc -l	;;   ", " \f\n\r\t\v", &j));
	return (0);
} */