/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:03:16 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/24 13:23:49 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "colors.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include <unistd.h>

char	*get_new_prompt(t_data *data, char *prompt)
{
	char	*tmp;
	char	*path;
	char	*exit_value;
	char	*home;
	char	*pwd;

	home = get_env_value("HOME", data->env);
	pwd = get_env_value("PWD", data->env);
	if (!pwd)
		pwd = "minishell";
	if (ft_strncmp(pwd, home, ft_strlen(home)) == 0)
		tmp = ft_strjoin3("[~", pwd + ft_strlen(home), "]");
	else
		tmp = ft_strjoin3("[", pwd, "]");
	path = ft_strjoin3(CYAN, tmp, RESET);
	free(tmp);
	exit_value = ft_itoa(data->exit_value);
	tmp = ft_strjoin3("[", exit_value, "]");
	free(exit_value);
	exit_value = ft_strjoin3(YELLOW, tmp, RESET);
	free(tmp);
	prompt = ft_strjoin3(path, exit_value, "$ ");
	free(path);
	free(exit_value);
	return (prompt);
}
