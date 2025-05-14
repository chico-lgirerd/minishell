/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:15:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/14 14:43:38 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "colors.h"
#include "libft.h"
#include <readline/readline.h>
#include <fcntl.h>

static void	read_stdin(int fd, char *delim) //rajouter data pour exit free
{
	char	*buff;
	
	while (1)
	{
		buff = NULL;
		buff = readline("> ");
		if (!buff)
		{
			ft_putstr_fd(RED"warning: here-doc document delimited by end-of", 2);
			ft_putstr_fd("-file (wanted '", 2);
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

void	heredoc(t_command *cmd, char *delim) //rajouter data pour exit free
{
	int	fd;

	fd = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		exit(10000);
	read_stdin(fd, delim);
	cmd->heredoc_fd = open(".heredoc.tmp", O_RDONLY, 0644);
	if (cmd->heredoc_fd > 0)
		unlink(".heredoc.tmp");
}
