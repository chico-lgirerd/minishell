/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:42:23 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/05 16:43:26 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "colors.h"
#include "parsing.h"
#include <stdlib.h>
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
	filename = ft_strjoin3(prefix, random_hex, suffix);
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
	free_all_data(data, true);
	return (errcode);
}
