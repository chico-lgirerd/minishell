/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:38:05 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/23 16:03:53 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include "parsing.h"

void	ft_sigaction(int signum, void *handler, bool use_siginfo);
void	free_strs(char **strs);
void	ft_error(char *str);
void	print_list(t_args *head);
void	print_command(t_command *head);
int		onlyspace(const char *str);
int		ft_isspace(char c);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
bool	token_is_pipe(char *content);
bool	token_is_redirection(char *content);

#endif
