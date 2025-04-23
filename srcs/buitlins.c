/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitlins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:58:23 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/23 18:08:39 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "minishell.h"

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

void	execute_builtin(t_command *cmd, char ***envp)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		g_exit_value = ft_echo(cmd->args + 1);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		g_exit_value = cd(cmd->args + 1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		g_exit_value = env(envp);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		g_exit_value = ft_exit(cmd->args[1]);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		g_exit_value = export(cmd->args[1], envp);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		g_exit_value = pwd();
	else if (ft_strcmp(cmd->args[0], "unset") == 0 && cmd->args[1])
		g_exit_value = unset(cmd->args[1], envp);
}
