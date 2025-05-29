/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:15:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/29 18:05:07 by tiaperei         ###   ########.fr       */
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
	free_all_data(data);
	return (errcode);
}

bool	is_quoted_delimiter(t_args *args_list, char *delim)
{
	t_args	*node;

	node = args_list;
	while (node)
	{
		if (node->content
			&& ft_strcmp(node->content, "<<") == 0
			&& node->next
			&& ft_strcmp(node->next->content, delim) == 0)
		{
			return node->next->in_quote;
		}
		node = node->next;
	}
	return false; // par défaut, on considère non quoted
}


void	input_to_fd(t_data *data, char *buff, int fd, char *delim)
{
	//t_args	*current;
	//bool	in_quote;

	current = data->args_list;
	printf("%s\n", delim);
	while (current)
	{
		if (current->content && ft_strcmp(current->content, delim) == 0)
		{
			in_quote = current->in_quote;
		}
		current = current->next;
	}
	printf("%s\n", delim);
	if (!is_quoted_delimiter(data->args_list, delim))
	{
		expand_arg(data, buff);
		ft_putendl_fd(data->expanded_arg, fd);
	}
	else
		ft_putendl_fd(buff, fd);
}

static void	read_stdin(t_data *data, int fd, char *delim)
{
	char	*buff;

	(void)data;
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
		input_to_fd(data, buff, fd, delim);
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
			exit(ENOMEM);
		fd = open(temp, O_WRONLY | O_CREAT, 0644);
		if (fd < 0)
		{
			free(temp);
			exit(output_file_error(errno, "heredoc_temp", data));
		}
		curr->tempfile = temp;
		read_stdin(data, fd, curr->delim);
		if (cmd->heredoc_fd > 2)
			close(cmd->heredoc_fd);
		cmd->heredoc_fd = open(temp, O_RDONLY, 0644);
		unlink(cmd->heredocs->tempfile);
		curr = curr->next;
	}
}
