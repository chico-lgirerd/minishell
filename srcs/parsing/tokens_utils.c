/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:10:22 by lgirerd           #+#    #+#             */
/*   Updated: 2025/07/01 13:27:51 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

int	token_is_pipe(char *content)
{
	return (ft_strcmp(content, "|") == 0);
}

int	token_is_redirection(char *content)
{
	return (ft_strcmp(content, "<") == 0
		|| ft_strcmp(content, ">") == 0
		|| ft_strcmp(content, "<<") == 0
		|| ft_strcmp(content, ">>") == 0);
}

int	token_is_operator(char *content)
{
	return (token_is_pipe(content) || token_is_redirection(content));
}

int	pipe_in_tokens(t_args *args_list)
{
	t_args	*curr;

	curr = args_list;
	while (curr)
	{
		if (token_is_pipe(curr->content))
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	heredoc_in_tokens(t_args *args_list)
{
	t_args	*curr;

	curr = args_list;
	while (curr)
	{
		if (ft_strcmp(curr->content, "<<") == 0)
			return (1);
		curr = curr->next;
	}
	return (0);
}
