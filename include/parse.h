/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:37:03 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/02 13:50:31 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PATH_MAX 4096

extern int	g_exit_value;
extern char	*g_cwd;

typedef struct s_args_list
{
	char				*content;
	struct s_args_list	*next;
	struct s_args_list	*prev;
}	t_args_list;

typedef struct s_data
{
	char		*line;
	t_args_list	*args_list;
}	t_data;

#endif