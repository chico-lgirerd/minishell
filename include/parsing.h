/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:37:03 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/02 18:30:45 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>

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

// INIT_PARSING
void	init_data(t_data *data);
void	init_args(t_args_list *args);

// PARSING
void	parsing_args(t_args_list **args_list, char *line);
void	append_node(t_args_list **args, char *content);

// FREE_DATA
void	free_all_data(t_data *data);
void	free_args_list(t_args_list **args_list);

#endif