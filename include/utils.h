/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:38:05 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/01 15:40:24 by tiaperei         ###   ########.fr       */
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
void	ft_error(t_data *data, char *str);
void	print_list(t_args *head);
void	print_command(t_command *head);
int		onlyspace(const char *str);
int		ft_isspace(char c);
size_t	int_len(int n);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
char	*strjoin_and_free(char *s1, char *s2);
bool	token_is_pipe(char *content);
bool	token_is_redirection(char *content);

#endif
