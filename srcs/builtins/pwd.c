/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:15:53 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/20 18:15:44 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "colors.h"
#include "libft.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int	pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		if (errno == EACCES)
			ft_putstr_fd(RED"minishell: pwd: Permission denied\n"RESET, 2);
		else if (errno == ENOMEM)
			ft_putstr_fd(RED"minishell: pwd: Out of memory\n"RESET, 2);
		else if (errno == ERANGE)
			ft_putstr_fd(RED"minishell: pwd: Path too long\n"RESET, 2);
		else
			ft_putstr_fd(RED"minishell: pwd: Unknown error occurred\n"RESET, 2);
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
