/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:52:08 by tiaperei          #+#    #+#             */
/*   Updated: 2025/05/17 16:11:30 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "parsing.h"
#include "colors.h"
#include "colors.h"
#include "signals.h"

void	ft_sigaction(int signum, void *handler, bool use_siginfo)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (use_siginfo == true)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handler;
	}
	else
		sa.sa_handler = handler;
	if (sigaction(signum, &sa, NULL) == -1)
	{
		printf("sigaction failed\n");
		exit(EXIT_FAILURE);
	}
}

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
		printf("output_file: %s\n", current->output_file);
		printf("heredoc_delimiter: %s\n", current->heredoc_delimiter);
		printf("append_output: %d\n", current->append_output);
		printf("\n");
		current = current->next;
	}
}

int	char_is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	char_is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

void	skip_space(char *line, int *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
}

int	onlyspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

size_t	int_len(int n)
{
	size_t	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	i++;
	return (i);
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
		return (NULL);
	str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (str);
}

void	update_quote_status(t_data *data, char c)
{
	if (c == '\'' && data->quote == 0)
		data->quote = 1;
	else if (c == '"' && data->quote == 0)
		data->quote = 2;
}

bool	token_is_pipe(char *content)
{
	return (ft_strcmp(content, "|") == 0);
}

bool	token_is_redirection(char *content)
{
	return (ft_strcmp(content, "<") == 0
		|| ft_strcmp(content, ">") == 0
		|| ft_strcmp(content, "<<") == 0
		|| ft_strcmp(content, ">>") == 0);
}

bool	token_is_operator(char *content)
{
	return (token_is_pipe(content) || token_is_redirection(content));
}

int	pipe_in_tokens(t_args *args_list)
{
	t_args	*curr;

	curr = args_list;
	while (curr)
	{
		if (token_is_pipe(curr->content))
			return (1);
		curr = curr->next;
	}
	return (0);
}
