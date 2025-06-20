/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:34:07 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/20 19:31:21 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "colors.h"
#include <stdio.h>

int	is_numeric(char *s)
{
	if (!s || *s == '\0')
		return (0);
	if (*s == '+' || *s == '-')
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

void	exit_non_numeric(t_data *data, char *arg)
{
	ft_putstr_fd(RED"minishell: exit: "RESET, 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(RED": numeric argument required"RESET, 2);
	free_all_data(data, true);
	exit(2);
}

int	ft_exit(char **args, t_data *data)
{
	long long	exitcode;

	printf("exit\n");
	if (!args[0])
	{
		free_all_data(data, true);
		exit(data->exit_value);
	}
	if (!is_numeric(args[0]))
		exit_non_numeric(data, args[0]);
	if (args[1])
	{
		ft_putendl_fd(RED"minishell: exit: too many arguments"RESET, 2);
		return (1);
	}
	exitcode = ft_atoll(args[0]);
	if ((exitcode == -1 || exitcode == 0) && (ft_strcmp(args[0], "-1")
			!= 0 && ft_strcmp(args[0], "0")))
		exit_non_numeric(data, args[0]);
	free_all_data(data, true);
	exit((int)exitcode % 256);
}
