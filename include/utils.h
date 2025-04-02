/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:38:05 by lgirerd           #+#    #+#             */
/*   Updated: 2025/04/02 16:56:31 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include "parse.h"

void	ft_sigaction(int signum, void *handler, bool use_siginfo);
void	free_all_data(t_data *data);
void	free_args_list(t_args_list **s_args_list);
void	free_args(char **args);
void	ft_error(char *str);
void	print_list(t_args_list *head);

#endif
