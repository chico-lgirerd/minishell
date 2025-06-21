/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:45:26 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/21 17:00:11 by tiaperei         ###   ########.fr       */
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
		exit_expand(data, sub_arg, tmp, NULL);
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
		exit_expand(data, sub_arg, tmp, NULL);
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
	tab = ft_split_charset(var_value, " \f\n\r\t\v");
	if (!tab)
		exit_expand(data, sub_arg, tmp, tab);
	data->original_tab = tab;
	if (data->arg && (!data->last_expand || tab[i + 1]))
	{
		tmp = strjoin_and_free(data, data->arg, tab[i]);
		if (!tmp)
			exit_expand(data, sub_arg, tmp, tab);
		if (!tab[i + 1])
			return (dup_tmp_and_free(data, sub_arg, tmp, tab));
		append_node(data, &data->args_list, tmp, false);
		i++;
		tmp = NULL;
		data->arg = NULL;
	}
	j = split_expand(data, sub_arg, tab + i, j);
	free(data->original_tab);
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
		exit_expand(data, sub_arg, NULL, NULL);
	var_value = get_env_value(var_name, data->env);
	free(var_name);
	if (var_value)
		j = expand_no_quote(data, var_value, sub_arg, j);
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
		exit_expand(data, sub_arg, NULL, NULL);
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
		exit_expand(data, sub_arg, tmp, NULL);
	free(tmp);
	return (j);
}

void	expand_arg_no_quote(t_data *data, char *sub_arg)
{
	int		i;
	int		j;

	data->expanded_arg = malloc(expanded_arg_size_no_quote(data, sub_arg) + 1);
	if (!data->expanded_arg)
		exit_expand(data, sub_arg, NULL, NULL);
	i = 0;
	j = 0;
	data->last_pos = find_last_expand(sub_arg);
	data->last_expand = false;
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
