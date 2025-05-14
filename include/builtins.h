/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:12:51 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/14 15:31:13 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parsing.h"
# include "pipes.h"

int		cd(char **args);
int		ft_echo(char **args);
int		env(char **envp);
int		print_export_list(char **envp);
int		valid_var_name(char *var);
int		export(char **args, t_data *data, char *var);
int		pwd(void);
int		ft_exit(char **args, t_data *data);
int		unset(char	**args, char ***envp);

int		envplen(char **envp);
int		execute_builtin(t_command *cmd, t_data *data);
int		is_builtin(char *cmd);
int		run_builtins(t_command *cmd, t_data *data);
int		output_id_error(char *arg);

#endif
