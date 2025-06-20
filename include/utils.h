/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:38:05 by lgirerd           #+#    #+#             */
/*   Updated: 2025/06/20 22:44:21 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include "parsing.h"

int		char_is_quote(char c);
int		char_is_operator(char c);
int		ft_isspace(char c);
void	skip_space(char *line, int *i);
int		onlyspace(const char *str);
size_t	int_len(int n);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
char	*strjoin_and_free(t_data *data, char *s1, char *s2);
int		update_quote_status(t_data *data, char c);
int		token_is_pipe(char *content);
int		token_is_redirection(char *content);
int		token_is_operator(char *content);
int		pipe_in_tokens(t_args *args_list);
int		heredoc_in_tokens(t_args *args_list);
void	print_syntax_error(char *token, int fd);
void	ft_error(t_data *data, char *str, int errcode);
void	print_eof_warning(char *delim);
int		print_dollar(t_data *data, int *i, int *j);
int		find_last_expand(char *sub_arg);
int		handle_arg_before(t_data *data, char *sub_arg, char **tab);
void	input_to_fd(t_data *data, char *buff, int fd, char *delim);

#endif
