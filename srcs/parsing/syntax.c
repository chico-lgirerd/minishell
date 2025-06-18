/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:29:41 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/18 08:55:11 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

#include "libft.h"

int	check_pipe_syntax(t_data *data, t_args *cur)
{
	if ((token_is_pipe(cur->content) && !cur->in_quote)
		&& (!cur->prev || !cur->next || !cur->next->content
			|| token_is_pipe(cur->next->content)))
	{
		print_syntax_error("|", 2);
		data->exit_value = 2;
		return (0);
	}
	return (1);
}

int	check_redir_syntax(t_data *data, t_args *cur)
{
	if ((token_is_redirection(cur->content) && !cur->in_quote)
		&& (!cur->next || !cur->next->content
			|| token_is_redirection(cur->next->content)))
	{
		if (cur->next)
			print_syntax_error(cur->next->content, 2);
		else
			print_syntax_error("newline", 2);
		data->exit_value = 2;
		return (0);
	}
	return (1);
}

int	validate_syntax(t_data *data, t_args *args_list)
{
	t_args	*cur;

	cur = args_list;
	while (cur)
	{
		if ((ft_strcmp(cur->content, "<<") == 0) && (!cur->prev || !cur->prev->content))
		{
			printf("Heredoc without command\n");
			return (0);
		}
		if (!check_pipe_syntax(data, cur)
			|| !check_redir_syntax(data, cur))
			return (0);
		cur = cur->next;
	}
	return (1);
}
