/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:00:53 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/18 22:02:21 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"
#include "utils.h"

static void	free_and_exit(t_data *data, char *sub_arg, char *str)
{
	if (data->arg)
		free(data->arg);
	if (data->expanded_arg)
		free(data->expanded_arg);
	free(sub_arg);
	ft_error(data, str, 12);
}

static int	handle_exit_status(t_data *data, char *sub_arg, int j)
{
	char	*exit_str;
	int		exit_len;

	exit_str = NULL;
	if (g_signal)
	{
		exit_str = ft_itoa(g_signal + 128);
		g_signal = 0;
	}
	else
		exit_str = ft_itoa(data->exit_value);
	if (!exit_str)
		free_and_exit(data, sub_arg, "malloc: failed in handle_exit_status");
	exit_len = ft_strlen(exit_str);
	ft_memcpy(data->expanded_arg + j, exit_str, exit_len);
	j += exit_len;
	free(exit_str);
	return (j);
}

static void	expand_no_quote(t_data *data, char *var_value, int *j)
{
	char	**tab;
	char	*tmp;
	int		i;
	
	tab = ft_split(var_value, ' ');
	i = 0;
	if (!tab[i + 1])
	{
		printf("j = %d\n", *j);
		printf("data->expanded_arg = %s\n", data->expanded_arg);
		ft_memcpy(data->expanded_arg + *j, tab[i], ft_strlen(tab[i]));
		data->expanded_arg[*j + ft_strlen(tab[i])] = '\0';
		*j += ft_strlen(tab[i]);
		if (data->arg)
		{
			/* tmp = ft_strjoin(data->arg, data->expanded_arg);
			append_node(data, &data->args_list, tmp, false);
			data->arg = NULL; */
		}
		return ;
	}
	if (data->arg)
	{
		printf("111111\n");
		tmp = ft_strjoin(data->arg, tab[i]);
		append_node(data, &data->args_list, tmp, false);
		i++;
		data->arg = NULL;
	}
	if (*j != 0)
	{
		printf("data->expanded_arg = %s\n", data->expanded_arg);

		tmp = ft_strjoin(data->expanded_arg, tab[i]);
		append_node(data, &data->args_list, tmp, false);
		i++;
		*j = 0;
	}
	while (tab[i])
	{
		if (!tab[i + 1])
		{
			ft_memcpy(data->expanded_arg + *j, tab[i], ft_strlen(tab[i]));
			data->expanded_arg[*j + ft_strlen(tab[i])] = '\0';
			i++;
			break ;
		}
		append_node(data, &data->args_list, tab[i], false);
		i++;
	}
	*j = ft_strlen(tab[i - 1]);
	//printf("j = %d\n", *j);
}


static void	handle_expand(t_data *data, char *sub_arg, int *i, int *j)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *i;
	while (sub_arg[*i] && (ft_isalnum(sub_arg[*i]) || sub_arg[*i] == '_'))
		(*i)++;
	if (start == *i)
		data->expanded_arg[(*j)++] = '$';
	var_name = ft_substr(sub_arg, start, (*i) - start);
	if (!var_name)
		free_and_exit(data, sub_arg, "malloc: failed in handle_env_var");
	var_value = get_env_value(var_name, data->env);
	free(var_name);
	if (var_value)
	{
		if (data->quote == 0)
			expand_no_quote(data, var_value, j);
		else
		{
			//printf("j = %d\n", *j);
			ft_memcpy(data->expanded_arg + *j, var_value, ft_strlen(var_value));
			*j += ft_strlen(var_value);
		}
	}
}

char	*get_env_value(char *var_name, t_env *env)
{
	int		var_len;
	t_env	*curr;

	var_len = ft_strlen(var_name);
	curr = env;
	while (curr)
	{
		if (ft_strncmp(curr->var, var_name, var_len) == 0
			&& curr->var[var_len] == '=')
			return (curr->var + var_len + 1);
		curr = curr->next;
	}
	return (NULL);
}

void	expand_arg(t_data *data, char *sub_arg)
{
	int		i;
	int		j;

	printf("data->expanded_size = %zu\n", expanded_arg_size(data, sub_arg) + 1);
	data->expanded_arg = malloc(expanded_arg_size(data, sub_arg) + 1);
	if (!data->expanded_arg)
		free_and_exit(data, sub_arg, "malloc: failed in expand_arg");
	i = 0;
	j = 0;
	while (sub_arg[i])
	{
		if (sub_arg[i] == '$' && sub_arg[i + 1] && ++i)
		{
			if (sub_arg[i] == '?' && ++i)
				j = handle_exit_status(data, sub_arg, j);
			else
				handle_expand(data, sub_arg, &i, &j);
		}
		else
			data->expanded_arg[j++] = sub_arg[i++];
	}
	data->expanded_arg[j] = '\0';
}
