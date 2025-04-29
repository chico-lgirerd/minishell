/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:12:51 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/26 17:50:41 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parsing.h"

int		cd(char **args);
int		ft_echo(char **args);
int		env(char **envp);
int		print_export_list(char **envp);
int		export(char **args, char ***envp);
int		pwd(void);
int		ft_exit(char **args, t_data *data);
int		unset(char	**args, char ***envp);

int		envplen(char **envp);
void	execute_builtin(t_command *cmd, char ***envp, t_data *data);
int		is_builtin(char *cmd);

#endif
