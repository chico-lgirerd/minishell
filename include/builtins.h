/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:12:51 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/26 15:59:59 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		cd(char **args);
int		ft_echo(char **args);
int		env(char **envp);
int		print_export_list(char **envp);
int		export(char **args, char ***envp);
int		pwd(void);
int		ft_exit(char **args);
int		unset(char	**args, char ***envp);

int		envplen(char **envp);
void	execute_builtin(t_command *cmd, char ***envp);
int		is_builtin(char *cmd);

#endif
