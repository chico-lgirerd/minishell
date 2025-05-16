/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:15:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/16 03:49:34 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "colors.h"
#include "libft.h"
#include <errno.h>
#include <readline/readline.h>
#include <fcntl.h>

int	dup_error(t_data *data, int errcode)
{
	if (errcode == EBADF)
		ft_putendl_fd(RED"minishell: dup/dup2: Bad file descriptor"RESET, 2);
	if (errcode == EMFILE)
		ft_putendl_fd(RED"minishell: dup/dup2: Too many open files"RESET, 2);
	free_all_data(data);
	return (errcode);
}

static void	read_stdin(int fd, char *delim) //rajouter data pour exit free
{
	char	*buff;

	while (1)
	{
		buff = NULL;
		buff = readline("> ");
		if (!buff)
		{
			ft_putstr_fd(RED"warning: here-doc document delimited by", 2);
			ft_putstr_fd(" end-of-file (wanted '", 2);
			ft_putstr_fd(delim, 2);
			ft_putstr_fd("')\n"RESET, 2);
			break ;
		}
		if (ft_strcmp(delim, buff) == 0)
			break ;
		ft_putendl_fd(buff, fd);
		free(buff);
	}
	if (buff)
		free(buff);
	close (fd);
}

void	heredoc(t_data *data, t_command *cmd, char *delim) //rajouter data pour exit free
{
	int	fd;

	fd = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		exit(output_file_error(errno, ".heredoc.tmp", data));
	read_stdin(fd, delim);
	cmd->heredoc_fd = open(".heredoc.tmp", O_RDONLY, 0644);
	if (cmd->heredoc_fd > 0)
		unlink(".heredoc.tmp");
}
