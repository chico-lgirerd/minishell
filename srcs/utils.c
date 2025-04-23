/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:52:08 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/23 13:50:55 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "parsing.h"
#include "color.h"

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

void	free_strs(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	print_list(t_args *head)
{
	t_args	*tail;

	printf("Liste dans l'ordre :\n");
	while (head)
	{
		printf("%s -> ", head->content);
		if (head->next == NULL)
			tail = head;
		head = head->next;
	}
	printf("NULL\n");
}

void	print_command(t_command *head)
{
	t_command	*current = head;
	int			i;

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

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
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
