/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:15:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/14 17:33:48 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "colors.h"
#include "minishell.h"
#include "signals.h"
#include "libft.h"
#include "utils.h"
#include "files.h"
#include <errno.h>
#include <readline/readline.h>
#include <fcntl.h>

static int	read_stdin(t_data *data, int fd, char *delim)
{
	char	*buff;

	(void)data;
	while (1)
	{
		buff = NULL;
		buff = readline("> ");
		if (g_signal == 2)
		{
			close(fd);
			free(buff);
			return (2);
		}
		if (!buff)
		{
			print_eof_warning(delim);
			break ;
		}
		if (ft_strcmp(delim, buff) == 0)
			break ;
		// input_to_fd(data, buff, fd, delim);
		ft_putendl_fd(buff, fd);
		free(buff);
	}
	if (buff)
		free(buff);
	close(fd);
	return (0);
}

void	heredoc(t_data *data, char *tempfile, char *delim)
{
	int	fd;
	int	result;

	fd = open(tempfile, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		exit(output_file_error(errno, "heredoc_temp", data));
	setup_heredoc_signals();
	result = read_stdin(data, fd, delim);
	free_all_data(data, true);
	if (result == 2)
		exit(130);
	exit(0);
}

static int	handle_child_result(t_data *data, t_command *cmd, t_heredoc *curr,
	int status)
{
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		if (cmd->heredoc_fd > 2)
			close(cmd->heredoc_fd);
		unlink(curr->tempfile);
		data->exit_value = 130;
		return (1);
	}
	if (cmd->heredoc_fd > 2)
		close(cmd->heredoc_fd);
	cmd->heredoc_fd = open(curr->tempfile, O_RDONLY, 0644);
	if (cmd->heredoc_fd == -1)
		ft_error(data, "failed to open heredoc fd", errno);
	unlink(curr->tempfile);
	return (0);
}

static int	launch_heredoc(t_data *data, t_command *cmd, t_heredoc *curr)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (create_temp_file(curr))
		ft_error(data, "heredoc: failed to create temp file", errno);
	pid = fork();
	if (pid == -1)
		ft_error(data, "fork: too many processes", errno);
	if (pid == 0)
		heredoc(data, curr->tempfile, curr->delim);
	waitpid(pid, &status, 0);
	return (handle_child_result(data, cmd, curr, status));
}

int	proc_heredoc(t_data *data, t_command *cmd)
{
	t_heredoc			*curr;
	int					exitcode;
	struct sigaction	original;
	struct sigaction	ignore;

	setup_signals_parent(&original, &ignore);
	curr = cmd->heredocs;
	while (curr)
	{
		exitcode = launch_heredoc(data, cmd, curr);
		if (exitcode)
		{
			sigaction(SIGINT, &original, NULL);
			return (130);
		}
		curr = curr->next;
	}
	sigaction(SIGINT, &original, NULL);
	return (0);
}
