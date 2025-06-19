/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:37:03 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/19 18:16:18 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include "pipes.h"

typedef struct s_env
{
	char			*var;
	int				index;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_args
{
	char			*content;
	bool			op_in_quote;
	struct s_args	*next;
	struct s_args	*prev;
}	t_args;

typedef struct s_heredoc
{
	char				*delim;
	char				*tempfile;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_redir
{
	char			*filename;
	int				append;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**args;
	int					count_args;
	int					number_cmds;
	bool				has_redirection;
	char				*input_file;
	t_heredoc			*heredocs;
	int					heredoc_fd;
	t_redir				*out_redir;
	int					append_output;
	struct s_command	*next;
}	t_command;

typedef struct s_data
{
	t_env		*env;
	char		*line;
	int			exit_value;
	int			quote;
	char		*arg;
	char		*expanded_arg;
	t_args		*args_list;
	t_command	*first_cmd;
	t_fork		forks;
	bool		test;
}	t_data;

// INIT_PARSING
void		init_data(t_data *data, char **env);
t_command	*init_command(void);
void		init_redir(t_data *data, t_command *cmd, char *file, int append);
t_env		*init_env(char **env);

// PARSING
void		parsing_args(t_data *data, char *line);
void		append_node(t_data *data, t_args **args,
				char *content, bool op_in_quote);
int			validate_syntax(t_data *data, t_args *args_list);

// EXPAND
void		expand_arg(t_data *data, char *arg);
size_t		expanded_arg_size(t_data *data, char *arg);
char		*get_env_value(char *var_name, t_env *env);

// COMMAND
void		build_command(t_data *data, t_args *args_list);

// FREE_DATA
void		free_all_data(t_data *data, bool free_env);
void		free_args_list(t_args **args_list);
void		free_command(t_command **first_cmd);

// ENV MANAGEMENT
t_env		*lstnew(char *content, int index);
void		lstadd_back(t_env **lstenv, t_env *newnode);
void		free_env_list(t_env *env);
char		**env_to_array(t_env *env);
int			get_env_size(t_env *env);

// REDIR & HEREDOC
void		add_heredoc(t_data *data, t_command *cmd, char *delim);
void		free_heredocs(t_command *cmd);

#endif
