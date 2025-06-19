/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:45:26 by tiaperei          #+#    #+#             */
/*   Updated: 2025/06/20 00:16:47 by tiaperei         ###   ########.fr       */
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

static int	handle_exit_status(t_data *data, char *sub_arg, int j, bool last_expand)
{
	char	*exit_str;
	int		exit_len;
	char	*tmp;

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
	if (last_expand)
	{
		exit_len = ft_strlen(exit_str);
		ft_memcpy(data->expanded_arg + j, exit_str, exit_len);
		j += exit_len;
	}
	else
	{
		tmp = ft_strjoin(data->arg, exit_str);
		printf("data->arg = %s\n", data->arg);
		data->arg = ft_strdup(tmp);
		printf("data->arg = %s\n", data->arg);
	}
	exit_len = ft_strlen(exit_str);
	j += exit_len;
	free(exit_str);
	return (j);
}

static int	expand_no_quote(t_data *data, char *var_value, char *sub_arg, int j, bool last_expand)
{
	int			i;
	char		*tmp;
	char		**tab;
	
	//printf("tmp1 = %s\n", tmp);
	//printf("data->expanded_arg = %s\n", data->expanded_arg);
	//printf("j = %d\n", j);
	i = 0;
	tmp = NULL;
	tab = ft_split(var_value, ' ');
	if (!tab)
		free_and_exit(data, sub_arg, "malloc: failed in expand_no_quote");
	if (data->arg && (!last_expand || tab[i + 1]))
	{
		//printf("1111111\n");
		tmp = strjoin_and_free(data->arg, tab[i]);
		if (!tmp)
			free_and_exit(data, sub_arg, "malloc: failed in expand_no_quote");
		if (!tab[i + 1])
		{
			data->arg = ft_strdup(tmp);
			free(tmp);
			tmp = NULL;
			free(tab);
			return (0);
		}
		append_node(data, &data->args_list, tmp, false);
		//printf("tmp2 = %s\n", tmp);
		i++;
		data->arg = NULL;
		tmp = NULL;
	}
	/* if (tmp)
	{
		printf("2222222\n");
		append_node(data, &data->args_list, tmp, false);
		tmp = NULL;
	} */
	/* if (j != 0 && !data->arg)
	{
		data->arg = ft_strdup(data->expanded_arg);
		//data->expanded_arg[0] = '\0';
		//free(data->expanded_arg);
		data->arg = ft_strjoin(data->expanded_arg, tab[i]);
		printf("data->arg = %s\n", data->arg);
		
		append_node(data, &data->args_list, data->arg, false);
		i++;
	} */
	while (tab[i])
	{
		if (!(tab[i + 1]))
		{
			if (last_expand)
			{
				//printf("3333333\n");
				ft_memcpy(data->expanded_arg + j, tab[i], ft_strlen(tab[i]));
				j += ft_strlen(tab[i]);
				free(tab[i]);
				break ;
			}
			data->arg = ft_strdup(tab[i]);
			free(tab[i]);
			break ;
		}
		append_node(data, &data->args_list, tab[i], false);
		i++;
	}
	free(tab);
	return (j);
}

static int	handle_env_var(t_data *data, char *sub_arg, int *i, int j, bool last_expand)
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
		j = expand_no_quote(data, var_value, sub_arg, j, last_expand);
	free(var_name);
	return (j);
}

void	expand_arg_no_quote(t_data *data, char *sub_arg)
{
	int		i;
	int		j;
	int		last;
	bool	last_expand;

	printf("data->arg = %s\n", data->arg);
	//printf("data->expanded_size = %zu\n", expanded_arg_size(data, sub_arg));
	data->expanded_arg = malloc(expanded_arg_size(data, sub_arg) + 1);
	//data->expanded_arg = malloc(sizeof(char) * 2);
	if (!data->expanded_arg)
		free_and_exit(data, sub_arg, "malloc: failed in expand_arg");
	i = 0;
	j = 0;
	last = find_last_expand(sub_arg);
	//printf("last = %d\n", last);
	last_expand = false;
	while (sub_arg[i])
	{
		if (sub_arg[i] == '$' && sub_arg[i + 1] && ++i)
		{
			if (last == i)
				last_expand = true;
			if (sub_arg[i] == '?' && ++i)
				j = handle_exit_status(data, sub_arg, j, last_expand);
			else
				j = handle_env_var(data, sub_arg, &i, j, last_expand);
		}
		else
			data->expanded_arg[j++] = sub_arg[i++];
	}
	data->expanded_arg[j] = '\0';
}
