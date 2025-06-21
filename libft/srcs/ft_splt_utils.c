/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:34:45 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/21 15:40:59 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_words_charset(char const *s, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!in_charset(s[i], charset) && s[i])
		count++;
	while (s[i])
	{
		while (in_charset(s[i], charset))
		{
			if (!in_charset(s[i + 1], charset) && s[i + 1] != '\0')
				count++;
			i++;
		}
		i++;
	}
	return (count);
}
