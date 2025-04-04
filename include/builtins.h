/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:12:51 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/04 11:05:12 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	cd(char *dirname);
void	ft_echo(char *args, char **env);
void	env(char **envp);
void	export(char *input, char ***envp);
void	pwd(void);
void	ft_exit(char *code);
void	unset(char	*input, char ***envp);

int		envplen(char **envp);

#endif
