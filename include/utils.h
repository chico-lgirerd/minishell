/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:38:05 by lgirerd           #+#    #+#             */
/*   Updated: 2025/07/01 13:26:41 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

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
void	ft_error(t_data *data, char *str, int errcode);
void	print_eof_warning(char *delim);
int		print_dollar(t_data *data, int *i, int *j);
int		find_last_expand(char *sub_arg);
int		dup_tmp_and_free(t_data *data, char *sub_arg, char *tmp, char **tab);
int		split_expand(t_data *data, char *sub_arg, char **tab, int j);
void	exit_expand(t_data *data, char *sub_arg, char *tmp, char **tab);
t_args	*ft_lstlast_args(t_args *lst);
char	*get_new_prompt(t_data *data, char *prompt);

int	empty_in_tokens(t_args *args_list);

#endif
