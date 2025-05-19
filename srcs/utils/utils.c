/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:52:08 by tiaperei          #+#    #+#             */
/*   Updated: 2025/05/19 17:19:47 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "parsing.h"
#include "colors.h"
#include "signals.h"

void	print_list(t_args *head)
{
	t_args	*tail;

	printf("Liste dans l'ordre :\n");
	while (head)
	{
		printf(BLUE"%s "RESET, head->content);
		printf(YELLOW"q = %d "RESET, head->quoted);
		printf("--> ");
		if (head->next == NULL)
			tail = head;
		head = head->next;
	}
	printf("NULL\n");
}

void	print_command(t_command *head)
{
	t_command	*current;
	int			i;

	current = head;
	while (current)
	{
		printf("Command with %d args:\n", current->count_args);
		for (i = 0; i < current->count_args; i++)
		{
			printf("  args[%d]: %s\n", i, current->args[i]);
		}
		printf("input_file: %s\n", current->input_file);
		if (current->out_redir)
		{
			printf("first out redir: %s\n", current->out_redir->filename);
			printf("append mode : %d\n", current->out_redir->append);
		}
		if (current->heredocs)
			printf("heredoc_delimiter: %s\n", current->heredocs->delim);
		printf("\n");
		current = current->next;
	}
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*str;

	if (!s2)
		return (s1);
	str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (str);
}

int	update_quote_status(t_data *data, char c)
{
	int	quote;

	quote = 0;
	if (c == '\'' && data->quote == 0)
		quote = 1;
	else if (c == '"' && data->quote == 0)
		quote = 2;
	return (quote);
}

void	print_syntax_error(char *token, int fd)
{
	const char	*error;

	error = "minishell: syntax error near unexpected token `";
	write(fd, error, ft_strlen(error));
	if (token)
		write(fd, token, ft_strlen(token));
	write(fd, "'\n", 2);
}

void	free_chars(char **chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		free(chars[i]);
		i++;
	}
	free(chars);
	chars = NULL;
}
