/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:37:03 by tiaperei          #+#    #+#             */
/*   Updated: 2025/05/10 15:27:07 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_command
{
	char				**args;
	int					count_args;
	bool				has_error;
	bool				has_redirection;
	char				*input_file;
	char				*output_file;
	char				*heredoc_delimiter;
	int					append_output;
	int					number_cmds;
	struct s_command	*next;
}	t_command;

typedef struct s_args
{
	char			*content;
	struct s_args	*next;
	struct s_args	*prev;
}	t_args;

typedef struct s_data
{
	char		**env;
	char		*line;
	char		*expanded_arg;
	t_args		*args_list;
	t_command	*first_cmd;
	int			touched_env;
}	t_data;

// INIT_PARSING
void		init_data(t_data *data, char **env);
void		init_args(t_args *args);
t_command	*init_command(void);

// PARSING
void		parsing_args(t_data *data, char *line);

// EXPAND
void		expand_arg(t_data *data, char *arg);
size_t		expanded_arg_size(char *arg, char **env);
char		*get_env_value(char *var_name, char **env);

// COMMAND
void		build_command(t_data *data, t_args *args_list);

// FREE_DATA
void		free_all_data(t_data *data);
void		free_args_list(t_args **args_list);
void		free_command(t_command **first_cmd);
void		free_command_redirection(t_command *cmd);


#endif
