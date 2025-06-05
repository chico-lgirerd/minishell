/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:15:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/05 16:44:32 by lgirerd          ###   ########lyon.fr   */
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
#include <sys/ioctl.h>

#include <stdio.h>

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

static int	read_stdin(t_data *data, int fd, char *delim)
{
	char	*buff;

	while (1)
	{
		buff = NULL;
		buff = readline("> ");
		if (g_signal == 2)
		{
			close(fd);
			return (2);
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
	if (result == 2)
		exit(130);
	exit(0);
}


int	proc_heredoc(t_data *data, t_command *cmd)
{
	pid_t		pid;
	int			status;
	t_heredoc	*curr;
	char		*temp;

	struct sigaction	old;
	struct sigaction	sa_ignore;
	status = 0;
	sigaction(SIGINT, NULL, &old);
	sa_ignore = old;
	sa_ignore.sa_handler = SIG_IGN;
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
			ft_error(data, "fork: too many processes");
		if (pid == 0)
			heredoc(data, curr->tempfile, curr->delim);
		else
		{
			waitpid(pid, &status, 0);
			if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT) ||
				(WIFEXITED(status) && WEXITSTATUS(status) == 130))
			{
				if (cmd->heredoc_fd > 2)
					close(cmd->heredoc_fd);
				unlink(curr->tempfile);
				data->exit_value = 130;
				sigaction(SIGINT, &old, NULL);
				return (130);
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
