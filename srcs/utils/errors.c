/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:52:52 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/24 13:21:16 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "cmd.h"
#include "libft.h"
#include "colors.h"

int	handle_not_found(char *cmd, t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, 2);
	if (cmd && cmd[0] != '\0')
		ft_putstr_fd(cmd, 2);
	else
		ft_putstr_fd("", 2);
	ft_putstr_fd(RED": command not found\n"RESET, 2);
	free_all_data(data, true);
	return (CMD_NOT_FOUND);
}

int	handle_noperm(char *cmd, t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(RED": Permission denied\n"RESET, 2);
	free_all_data(data, true);
	return (126);
}

int	handle_nofile(char *cmd, t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(RED": No such file or directory\n"RESET, 2);
	free_all_data(data, true);
	return (CMD_NOT_FOUND);
}

int	handle_point(t_data *data)
{
	ft_putstr_fd(RED"minishell: .: filename argument required\n.:", 2);
	ft_putstr_fd("usage: . filename [arguments]\n"RESET, 2);
	free_all_data(data, true);
	return (2);
}

int	quote_unclosed(char *line)
{
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && quote == 0)
			quote = 1;
		else if (line[i] == '\'' || line[i] == '"')
			quote = 0;
		i++;
	}
	return (quote);
}
