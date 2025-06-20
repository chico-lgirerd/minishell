/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:45:26 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 22:51:28 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"
#include "utils.h"

static int	handle_exit_status(t_data *data, char *sub_arg, int j)
{
	char	*exit_str;
	char	*tmp;

	exit_str = NULL;
	tmp = NULL;
	if (g_signal)
		exit_str = ft_itoa(g_signal + 128);
	else
		exit_str = ft_itoa(data->exit_value);
	if (!exit_str)
		free_and_exit(data, sub_arg, "malloc: failed in handle_exit_status");
	if (data->last_expand)
	{
		ft_memcpy(data->expanded_arg + j, exit_str, ft_strlen(exit_str));
		j += ft_strlen(exit_str);
		free(exit_str);
		return (j);
	}
	tmp = strjoin_and_free(data, data->arg, exit_str);
	data->arg = ft_strdup(tmp);
	if (!data->arg)
		free_and_exit(data, sub_arg, "malloc: failed in handle_exit_status");
	free(tmp);
	return (j);
}

static int	expand_no_quote(t_data *data, char *var_value, char *sub_arg, int j)
{
	int			i;
	char		*tmp;
	char		**tab;
	
	i = 0;
	tmp = NULL;
	tab = ft_split(var_value, ' ');
	if (!tab)
		free_and_exit(data, sub_arg, "malloc: failed in expand_no_quote");
	if (data->arg && (!data->last_expand || tab[i + 1]))
	{
		
		tmp = strjoin_and_free(data, data->arg, tab[i]);
		if (!tmp)
			free_and_exit(data, sub_arg, "malloc: failed in expand_no_quote");
		if (!tab[i + 1])
		{
			data->arg = ft_strdup(tmp);
			if (!data->arg)
				free_and_exit(data, sub_arg, "malloc: failed in expand_no_quote"); //free tmp, tab
			free(tmp);
			tmp = NULL;
			free(tab);
			return (j);
		}
		append_node(data, &data->args_list, tmp, false);
		i++;
		data->arg = NULL;
		tmp = NULL;
	}
	while (tab[i])
	{
		if (!(tab[i + 1]))
		{
			if (data->last_expand)
			{
				printf("111111\n");
				ft_memcpy(data->expanded_arg + j, tab[i], ft_strlen(tab[i]));
				j += ft_strlen(tab[i]);
				free(tab[i]);
				break ;
			}
			data->arg = ft_strdup(tab[i]);
			if (!data->arg)
				free_and_exit(data, sub_arg, "malloc: failed in expand_no_quote");// free tab[i]
			free(tab[i]);
			break ;
		}
		append_node(data, &data->args_list, tab[i], false);
		i++;
	}
	free(tab);
	return (j);
}

static int	handle_env_var(t_data *data, char *sub_arg, int *i, int j)
{
	int		start;
	char	*var_name;
	char	*var_value;
	
	start = *i;
	while (sub_arg[*i] && (ft_isalnum(sub_arg[*i]) || sub_arg[*i] == '_'))
		(*i)++;
	if (start == *i)
	{
		data->expanded_arg[j++] = '$';
		return (j);
	}
	var_name = ft_substr(sub_arg, start, (*i) - start);
	if (!var_name)
		free_and_exit(data, sub_arg, "malloc: failed in handle_env_var");
	var_value = get_env_value(var_name, data->env);
	if (var_value)
		j = expand_no_quote(data, var_value, sub_arg, j);
	free(var_name);
	return (j);
}

static int	handle_other(t_data *data, char *sub_arg, int *i, int j)
{
	int		start;
	char	*str;
	char	*tmp;
	
	start = *i;
	while (sub_arg[*i] && sub_arg[*i] != '$')
		(*i)++;
	if (start == *i)
		return (print_dollar(data, i, &j));
	str = ft_substr(sub_arg, start, (*i) - start);
	if (!str)
		free_and_exit(data, sub_arg, "malloc: failed in handle_other");
	if (data->last_pos == -1 || start > data->last_pos)
	{
		ft_memcpy(data->expanded_arg + j, str, ft_strlen(str));
		j += ft_strlen(str);
		free(str);
		return (j);
	}
	tmp = strjoin_and_free(data, data->arg, str);
	data->arg = ft_strdup(tmp);
	if (!data->arg)
		free_and_exit(data, sub_arg, "malloc: failed in handle_other");
	free(tmp);
	return (0);
}

void	expand_arg_no_quote(t_data *data, char *sub_arg)
{
	int		i;
	int		j;

	printf("data->expanded_size = %zu\n", expanded_arg_size_no_quote(data, sub_arg) + 1);
	data->expanded_arg = malloc(expanded_arg_size_no_quote(data, sub_arg) + 1);
	if (!data->expanded_arg)
		free_and_exit(data, sub_arg, "malloc: failed in expand_arg");
	i = 0;
	j = 0;
	data->last_pos = find_last_expand(sub_arg);
	data->last_expand = false;
	printf("last = %d\n", data->last_pos);
	while (sub_arg[i])
	{
		if (sub_arg[i] == '$' && sub_arg[i + 1] && ++i)
		{
			if (data->last_pos == i)
				data->last_expand = true;
			if (sub_arg[i] == '?' && ++i)
				j = handle_exit_status(data, sub_arg, j);
			else
				j = handle_env_var(data, sub_arg, &i, j);
		}
		else
			j = handle_other(data, sub_arg, &i, j);
	}
	data->expanded_arg[j] = '\0';
}
