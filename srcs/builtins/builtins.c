/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:58:23 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/20 17:39:30 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include "parsing.h"
#include "builtins.h"
#include "colors.h"
#include "files.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0);
}

int	execute_builtin(t_command *cmd, t_data *data)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd->args + 1, data->first_cmd));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (cd(cmd->args + 1, data));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (env(data->env));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(cmd->args + 1, data));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (export(cmd->args + 1, data));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (unset(cmd->args + 1, data));
	return (1000);
}

int	run_builtins(t_command *cmd, t_data *data)
{
	int	saved_fds[2];
	int	returncode;

	setup_redirection(cmd, data, saved_fds);
	returncode = execute_builtin(cmd, data);
	if (returncode == 1000)
	{
		ft_putstr_fd(RED"minishell: builtins: failed to", 2);
		ft_putstr_fd(" execute a builtin\n"RESET, 2);
	}
	restore_fds(saved_fds, data);
	return (returncode);
}
