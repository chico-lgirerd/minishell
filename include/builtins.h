/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:12:51 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/13 15:28:18 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parsing.h"
# include "pipes.h"

int		cd(char **args, t_data *data);
int		ft_echo(char **args, t_command *cmd);
int		env(t_env *env);
int		print_export_list(t_data *data, t_env *env);
int		valid_var_name(char *var);
int		export(char **args, t_data *data);
int		pwd(void);
int		ft_exit(char **args, t_data *data);
int		unset(char	**args, t_data *data);
int		execute_builtin(t_command *cmd, t_data *data);
int		is_builtin(char *cmd);
int		run_builtins(t_command *cmd, t_data *data);
int		output_id_error(char *arg);
int		replace_existing(char *var, t_env *env);
int		add_new_var(t_data *data, char *var);
int		update_env_var(t_data *data, char *key, char *value);
int		get_export_size(t_env *env);
void	print_escaped(char *s);
void	swap_env(t_env **a, t_env **b);

#endif
