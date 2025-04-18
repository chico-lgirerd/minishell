/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:37:03 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/18 15:27:06 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_command
{
	char				**args;
	int					count_args;
	char				*input_file;
	char				*output_file;
	char				*heredoc_delimiter;
	int					append_output;
	struct s_command	*next;
}	t_command;

typedef struct s_args
{
	char			*content;
	int				in_quote;
	t_command		*first_cmd;
	struct s_args	*next;
	struct s_args	*prev;
}	t_args;

typedef struct s_data
{
	char	*line;
	t_args	*args_list;
}	t_data;

// INIT_PARSING
void		init_data(t_data *data);
void		init_args(t_args *args);
t_command	*init_command(void);

// PARSING
void		parsing_args(t_args **args_list, char *line);
void		parsing_quote(t_args **args_list, char *line, int s, int *i);
void		append_node(t_args **args, char *content, int quote);

t_command	*build_command(t_args **args_list);
void		append_new_command(t_command **first_cmd, t_command **current_cmd);
void		handle_redirection(t_command *cmd, t_args **current);
void		update_redirection(t_command *cmd, char *type, char *file);
void		add_argument(t_command *cmd, char *content, t_command *first_cmd);

// FREE_DATA
void		free_all_data(t_data *data);
void		free_args_list(t_args **args_list);
void		free_command(t_command **first_cmd);

#endif