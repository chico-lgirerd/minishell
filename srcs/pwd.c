/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:15:53 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/29 17:28:37 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "colors.h"
#include <unistd.h>
#include <stdio.h>

int	pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		if (errno == EACCES)
			printf(RED"minishell: pwd: Permission denied\n"RESET);
		else if (errno == ENOMEM)
			printf(RED"minishell: pwd: Out of memory\n"RESET);
		else if (errno == ERANGE)
			printf(RED"minishell: pwd: Path too long\n"RESET);
		else
			printf(RED"minishell: pwd: An unknown error occurred\n"RESET);
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}

