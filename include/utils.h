/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:38:05 by lgirerd           #+#    #+#             */
/*   Updated: 2025/05/18 19:06:17 by lgirerd          ###   ########lyon.fr   */
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
void	print_list(t_args *head);
void	print_command(t_command *head);
int		char_is_quote(char c);
int		char_is_operator(char c);
int		ft_isspace(char c);
void	skip_space(char *line, int *i);
int		onlyspace(const char *str);
size_t	int_len(int n);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
char	*strjoin_and_free(char *s1, char *s2);
int		update_quote_status(t_data *data, char c);
int		token_is_pipe(char *content);
int		token_is_redirection(char *content);
int		token_is_operator(char *content);
int		pipe_in_tokens(t_args *args_list);
void	print_syntax_error(char *token, int fd);
void	ft_error(t_data *data, char *str);

#endif
