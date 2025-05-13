/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:15:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/13 14:48:55 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "colors.h"
#include "libft.h"
#include <readline/readline.h>
#include <fcntl.h>

static void	read_stdin(t_data *data, int fd, char *delim)
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

int	heredoc(t_data *data, char *delim)
{
	int	fd;

	fd = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
		return (-1);
	read_stdin(data, fd, delim);
	// return le fd du fichier ou pas ? mettre le fichier en input file de la cmd ?
}
