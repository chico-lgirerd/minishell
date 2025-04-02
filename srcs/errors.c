/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:52:52 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/02 17:17:43 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "better_utils.h"
#include <stdio.h>

void	output_error(int errcode)
{
	const char	*red;
	const char	*reset;

	reset = "\033[0m";
	red = "\033[31m";
	write(2, red, 5);
	write(2, strerror(errcode), ft_strlen(strerror(errcode)));
	write(2, "\n", 2);
	write(2, reset, 4);
	// perror("Failed to open directory");
}
