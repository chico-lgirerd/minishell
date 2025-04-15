/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:52:08 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/15 20:40:07 by tiaperei         ###   ########.fr       */
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

void	print_list(t_args_list *head)
{
	t_args_list	*tail;

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

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
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
