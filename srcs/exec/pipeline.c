/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:01:19 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/05 16:38:08 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "pipes.h"
#include "cmd.h"
#include "errors.h"
#include "libft.h"
#include "colors.h"

static void	setup_child_pipes(t_data *data, int **pipes, int i, int cmd_count)
{
	int	j;

	if (i > 0 && dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
		exit(dup_error(data, errno));
	if (i < cmd_count - 1 && dup2(pipes[i][1], STDOUT_FILENO) == -1)
		exit(dup_error(data, errno));
	j = 0;
	while (j < cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

int	exit_pipeline(t_data *data, int errcode)
{
	if (errcode == EAGAIN)
		ft_putendl_fd(RED"minishell: fork: temporarily unavailable"RESET, 2);
	if (errcode == ENOMEM)
		ft_putendl_fd(RED"minishell: malloc: cannot allocate memory"RESET, 2);
	if (errcode == EMFILE || errcode == EFAULT)
		ft_putendl_fd(RED"minishell: too many open files"RESET, 2);
	free_all_data(data, true);
	return (errcode);
}

void	fork_commands(t_command *first_cmd, t_fork *forks, t_data *data)
{
	t_command	*curr;
	int			i;

	curr = first_cmd;
	i = -1;
	while (++i < forks->num_cmds && curr)
	{
		if (proc_heredoc(data, curr) == 130)
			data->exit_value = 130;
		forks->pids[i] = fork();
		if (forks->pids[i] == -1)
			exit(exit_pipeline(data, errno));
		if (forks->pids[i] == 0)
		{
			if (!curr->args || !curr->args[0] || curr->args[0][0] == '\0')
				exit(handle_not_found(curr->args[0], data));
			setup_child_pipes(data, forks->pipes, i, forks->num_cmds);
			curr->number_cmds = forks->num_cmds;
			execute_command(curr, forks, data);
			ft_error(data, "An unknown error occured");
		}
		if (curr->heredoc_fd > 2)
			close(curr->heredoc_fd);
		curr = curr->next;
	}
}

static int	wait_childs(t_data *data, int num_cmds)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < num_cmds)
	{
		if (i == num_cmds - 1)
			waitpid(data->forks.pids[i], &status, 0);
		else
			waitpid(data->forks.pids[i], NULL, 0);
		i++;
	}
	free(data->forks.pids);
	data->forks.pids = NULL;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_pipeline(t_command *first_cmd, t_data *data)
{
	int		**pipes;
	pid_t	*pids;
	int		num_cmds;

	num_cmds = count_commands(first_cmd);
	first_cmd->number_cmds = num_cmds;
	pipes = create_pipes(data, num_cmds - 1);
	if (!pipes)
		exit(exit_pipeline(data, errno));
	pids = malloc(sizeof(pid_t) * num_cmds);
	if (!pids)
		exit(exit_pipeline(data, errno));
	data->forks.num_cmds = num_cmds;
	data->forks.pipes = pipes;
	data->forks.pids = pids;
	fork_commands(first_cmd, &data->forks, data);
	if (data->exit_value == 130)
		return (130);
	close_free_pipes(data->forks.pipes, num_cmds - 1);
	data->forks.pipes = NULL;
	return (wait_childs(data, num_cmds));
}
