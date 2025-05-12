/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:54:27 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/12 13:31:42 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "libft.h"
#include "colors.h"

void	heredoc_input(int pipe_fd, char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd(RED"minishell: warning: here-doc document \
				delimited by end-of-file (wanted '"RESET, 2);
			ft_putstr_fd(delim, 2);
			ft_putstr_fd(RED"')\n"RESET, 2);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fd);
		ft_putstr_fd("\n", pipe_fd);
		free(line);
	}
}

int	run_heredoc(t_command *cmd)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	heredoc_input(pipe_fd, cmd->heredoc_delimiter);
	close(pipe_fd);
	cmd->heredoc_fd = pipe_fd[0];
	return (0);
}

void	run_all_heredoc(t_command *cmd)
{
	t_command	*curr;

	curr = cmd;
	while (curr)
	{
		if (curr->heredoc_delimiter && run_heredoc(curr) == -1)
			exit(10000);
		curr = curr->next;
	}
}
