/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:52:08 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 17:44:33 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "parsing.h"
#include "colors.h"
#include "signals.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*str;

	if (!s2)
		return (s1);
	str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (str);
}

int	update_quote_status(t_data *data, char c)
{
	int	quote;

	quote = 0;
	if (c == '\'' && data->quote == 0)
		quote = 1;
	else if (c == '"' && data->quote == 0)
		quote = 2;
	return (quote);
}

void	print_syntax_error(char *token, int fd)
{
	const char	*error;

	error = "minishell: syntax error near unexpected token `";
	write(fd, error, ft_strlen(error));
	if (token)
		write(fd, token, ft_strlen(token));
	write(fd, "'\n", 2);
}

void	free_chars(char **chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		free(chars[i]);
		i++;
	}
	free(chars);
	chars = NULL;
}

t_args	*ft_lstlast_args(t_args *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
