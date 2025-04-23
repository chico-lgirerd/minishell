/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:12:51 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/23 17:53:39 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	cd(char **args);
int	ft_echo(char **args);
int	env(char **envp);
void	export(char *input, char ***envp);
void	pwd(void);
int	ft_exit(char **args);
void	unset(char	*input, char ***envp);

int		envplen(char **envp);
void	execute_builtin(t_command *cmd, char ***envp);

#endif
