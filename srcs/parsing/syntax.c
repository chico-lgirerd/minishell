/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:29:41 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/23 15:37:27 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include "libft.h"
#include "files.h"
#include <unistd.h>

void	print_syntax_error(char *token, int fd)
{
	const char	*error;

	error = "minishell: syntax error near unexpected token `";
	write(fd, error, ft_strlen(error));
	if (token)
		write(fd, token, ft_strlen(token));
	write(fd, "'\n", 2);
}

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

int	no_cmd_heredoc(t_data *data, t_command *cmd, t_args *cur)
{
	cmd = init_command();
	data->first_cmd = cmd;
	while (ft_strcmp(cur->content, "<<") == 0)
	{
		add_heredoc(data, cmd, cur->next->content);
		if (cur->next && cur->next->next)
			cur = cur->next->next;
		else
			cur = cur->next;
	}
	data->exit_value = proc_heredoc(data, cmd);
	close(cmd->heredoc_fd);
	return (2);
}

int	validate_syntax(t_data *data, t_args *args_list)
{
	t_args		*cur;
	t_command	*cmd;

	cur = args_list;
	cmd = NULL;
	while (cur)
	{
		if (!check_pipe_syntax(data, cur)
			|| !check_redir_syntax(data, cur))
			return (0);
		if ((ft_strcmp(cur->content, "<<") == 0)
			&& (!cur->prev || (!cur->prev->content || !ft_strcmp(cur->prev->content, "|"))
			return (no_cmd_heredoc(data, cmd, cur));
		cur = cur->next;
	}
	return (1);
}
