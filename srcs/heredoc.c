/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:15:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/19 10:39:02 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "colors.h"
#include "libft.h"
#include "utils.h"
#include <errno.h>
#include <readline/readline.h>
#include <fcntl.h>

static char	*generate_hex(const char *hexadecimal)
{
	int				fd;
	unsigned char	bytes[6];
	char			*hex;
	int				i;
	
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0 || read(fd, bytes, 6) != 6)
	{
		if (fd >= 0)
			close(fd);
		return (NULL);
	}
	close(fd);
	hex = malloc(13);
	if (!hex)
		return (NULL);
	i = -1;
	while (++i < 6)
	{
		hex[i * 2] = hexadecimal[bytes[i] >> 4];
		hex[i * 2 + 1] = hexadecimal[bytes[i] & 0x0F];
	}
	hex[12] = '\0';
	return (hex);
}

static char	*generate_temp(void)
{
	char	*random_hex;
	char	*filename;
	char	*prefix;
	char	*suffix;

	prefix = ".heredoc_";
	suffix = ".tmp";
	random_hex = generate_hex("0123456789abcdef");
	if (!random_hex)
		return (NULL);
	filename = ft_strjoin3(prefix, random_hex, suffix);;
	free(random_hex);
	if (!filename)
		return (NULL);
	return (filename);
}

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

void	heredoc(t_data *data, t_command *cmd) //rajouter data pour exit free
{
	int			fd;
	char		*temp;
	t_heredoc	*curr;
	
	curr = cmd->heredocs;
	while (curr)
	{
		temp = generate_temp();
		if (!temp)
			exit(1);
		fd = open(temp, O_WRONLY | O_CREAT, 0644);
		if (fd < 0)
		{
			free(temp);
			exit(output_file_error(errno, "heredoc_temp", data));
		}
		curr->tempfile = temp;
		read_stdin(fd, curr->delim);
		if (cmd->heredoc_fd > 2)
			close(cmd->heredoc_fd);
		cmd->heredoc_fd = open(temp, O_RDONLY, 0644);
		unlink(cmd->heredocs->tempfile);
		curr = curr->next;
	}
}

