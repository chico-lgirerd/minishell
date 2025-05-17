/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:37:03 by tiaperei          #+#    #+#             */
/*   Updated: 2025/05/17 17:33:09 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "pipes.h"
# include "files.h"

typedef struct s_env
{ 
	char			*var;
	int				index;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;


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
	bool				has_error;
	bool				has_redirection;
	char				*input_file;
	char				*output_file;
	char				*heredoc_delimiter;
	int					heredoc_fd;
	int					append_output;
	int					number_cmds;
	struct s_command	*next;
	t_redir				*out_redir;
}	t_command;

typedef struct s_args
{
	char			*content;
	bool			quoted;
	struct s_args	*next;
	struct s_args	*prev;
}	t_args;

typedef struct s_data
{
	t_env		*env;
	char		*line;
	int			quote;
	char		*expanded_arg;
	t_args		*args_list;
	t_command	*first_cmd;
	int			touched_env;
	t_fork		*forks;
}	t_data;

// INIT_PARSING
void		init_data(t_data *data, char **env);
void		init_args(t_args *args);
t_command	*init_command(void);

// PARSING
void		parsing_args(t_data *data, char *line);

// EXPAND
void		expand_arg(t_data *data, char *arg);
size_t		expanded_arg_size(char *arg, t_env *env);
char		*get_env_value(char *var_name, t_env *env);

// COMMAND
void		build_command(t_data *data, t_args *args_list);

// FREE_DATA
void		free_all_data(t_data *data);
void		free_args_list(t_args **args_list);
void		free_command(t_command **first_cmd);
void		free_command_redirection(t_command *cmd);

// ENV MANAGEMENT
t_env	*init_env(char **env);
t_env	*lstnew(char *content, int index);
void	lstadd_back(t_env **lstenv, t_env *newnode);
void	free_env_list(t_env *env);
char	**env_to_array(t_env *env);
int		get_env_size(t_env *env);

#endif
