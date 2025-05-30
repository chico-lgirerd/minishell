/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:15:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/30 17:43:58 by lgirerd          ###   ########lyon.fr   */
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

void	input_to_fd(t_data *data, char *buff, int fd)
{
	char	*expanded;

	if (1 == 1)
	{
		expand_arg(data, buff);
		expanded = data->expanded_arg;
		ft_putendl_fd(expanded, fd);
		free(expanded);
	}
	else
		ft_putendl_fd(buff, fd);
}

void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	g_exit_value = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_done = 1;
	// close(1);
	exit(130);
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
		input_to_fd(data, buff, fd);
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
	exit(0);
}


void	proc_heredoc(t_data *data, t_command *cmd)
{
	pid_t		pid;
	int			status;
	t_heredoc	*curr;
	char		*temp;

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
			if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			{
				g_exit_value = 130;
				if (cmd->heredoc_fd > 2)
					close(cmd->heredoc_fd);
				unlink(curr->tempfile);
				return ;
			}
			if (cmd->heredoc_fd > 2)
				close(cmd->heredoc_fd);
			cmd->heredoc_fd = open(curr->tempfile, O_RDONLY, 0644);
			unlink(curr->tempfile);
		}
		curr = curr->next;
	}
}


