/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:15:53 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/24 13:19:09 by lgirerd          ###   ########lyon.fr   */
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

	pwd = get_env_value("PWD", data->env);
	if (pwd == NULL)
		pwd = "PWD not set";
	printf("%s\n", pwd);
	return (0);
}
