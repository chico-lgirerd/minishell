/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:17:02 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/16 07:26:34 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	check_location(void *ptr)
{
	int	local;

	return ((char *)ptr > (char *)&local);
}

int	check_double_ptr_location(void **ptr)
{
	int		local;
	void	*stack_marker;

	stack_marker = &local;
	return ((char *)(*ptr) > (char *)stack_marker);
}

void	free_chars(char **chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		if (!check_location(chars[i]))
			free(chars[i]);
		i++;
	}
	if (!check_double_ptr_location((void *)chars))
		free(chars);
}

void	free_s(char *str, char **sstr)
{
	if (str)
		free(str);
	if (sstr)
		free_chars(sstr);
}
