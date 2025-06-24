/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:15:53 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/23 15:24:42 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "colors.h"
#include "libft.h"
#include "parsing.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int	pwd(t_data *data)
{
	char	*pwd;

	// if (getcwd(cwd, sizeof(cwd)) == NULL)
	pwd = get_env_value("PWD", data->env);
	if (pwd == NULL)
	{
		pwd = "FAIL";
		// if (errno == EACCES)
		// 	ft_putstr_fd(RED"minishell: pwd: Permission denied\n"RESET, 2);
		// else if (errno == ENOMEM)
		// 	ft_putstr_fd(RED"minishell: pwd: Out of memory\n"RESET, 2);
		// else if (errno == ERANGE)
		// 	ft_putstr_fd(RED"minishell: pwd: Path too long\n"RESET, 2);
		// else
		// 	ft_putstr_fd(RED"minishell: pwd: Unknown error occurred\n"RESET, 2);
		// return (1);
		
	}
	printf("%s\n", pwd);
	return (0);
}
