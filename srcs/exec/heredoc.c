/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:15:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/03 16:05:50 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "colors.h"
#include "minishell.h"
#include "signals.h"
#include "libft.h"
#include "utils.h"
#include <errno.h>
#include <readline/readline.h>
#include <fcntl.h>

#include <stdio.h>

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

void	input_to_fd(t_data *data, char *buff, int fd, char *delim)
{
	t_args	*current;
	bool	in_quote;

	current = data->args_list;
	while (current)
	{
		if (current->content && ft_strcmp(current->content, delim) == 0)
		{
			in_quote = current->in_quote;
		}
		current = current->next;
	}
	if (!in_quote)
	{
		expand_arg(data, buff);
		ft_putendl_fd(data->expanded_arg, fd);
	}
	else
		ft_putendl_fd(buff, fd);
}

void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	g_exit_value = 130;
	write(1, "\n", 1);
	close(0);
}

void	ignore_sigint(int signum)
{
	(void)signum;
}

void	setup_heredoc_signals(void)
{
	ft_sigaction(SIGINT, heredoc_sigint_handler, false);
	ft_sigaction(SIGQUIT, SIG_IGN, false);
}

static void	read_stdin(t_data *data, int fd, char *delim)
{
	char	*buff;

	while (1)
	{
		buff = NULL;
		buff = readline("> ");
		if (g_exit_value == 130)
		{
			break ;
		}
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

void	heredoc(t_data *data, char *tempfile, char *delim)
{
	int			fd;

	fd = open(tempfile, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
			exit(output_file_error(errno, "heredoc_temp", data));
	setup_heredoc_signals();
	read_stdin(data, fd, delim);
	exit(130);
}


int	proc_heredoc(t_data *data, t_command *cmd)
{
	pid_t		pid;
	int			status;
	t_heredoc	*curr;
	char		*temp;

	struct sigaction	old;
	struct sigaction	sa_ignore;

	sigaction(SIGINT, NULL, &old);
	sa_ignore = old;
	sa_ignore.sa_handler = ignore_sigint;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, NULL);
	
	curr = cmd->heredocs;
	while (curr)
	{
		temp = generate_temp();
		if (!temp)
			exit(ENOMEM);
		curr->tempfile = ft_strdup(temp);
		free(temp);
		pid = fork();
		if (pid == -1)
			exit(ENOMEM);
		if (pid == 0)
			heredoc(data, curr->tempfile, curr->delim);
		else
		{
			waitpid(pid, &status, 0);
			if (g_exit_value == 130)
			{
				if (cmd->heredoc_fd > 2)
					close(cmd->heredoc_fd);
				unlink(curr->tempfile);
				sigaction(SIGINT, &old, NULL);
				return (1);
			}
			if (cmd->heredoc_fd > 2)
				close(cmd->heredoc_fd);
			cmd->heredoc_fd = open(curr->tempfile, O_RDONLY, 0644);
			unlink(curr->tempfile);
		}
		curr = curr->next;
	}
	sigaction(SIGINT, &old, NULL);
	return (0);
}
