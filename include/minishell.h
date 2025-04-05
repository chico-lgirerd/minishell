/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:50:19 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/05 15:02:26 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define NO_QUOTE 0
#define SINGLE_QUOTE 1
#define DOUBLE_QUOTE 2

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PATH_MAX 4096

extern int	g_exit_value;

#endif