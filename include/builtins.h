/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:12:51 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/14 14:37:02 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parsing.h"
# include "pipes.h"

int		cd(char **args);
int		ft_echo(char **args, t_command *cmd);
int		env(char **envp);
int		print_export_list(char **envp);
int		valid_var_name(char *var);
int		export(char **args, t_data *data, char *var);
int		pwd(void);
int		ft_exit(char **args, t_data *data);
int		unset(char	**args, char ***envp);

int		envplen(char **envp);
int		execute_builtin(t_command *cmd, t_fork *forks, t_data *data);
int		is_builtin(char *cmd);

#endif
