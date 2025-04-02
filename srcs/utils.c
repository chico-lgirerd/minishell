/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:52:08 by tiaperei          #+#    #+#             */
/*   Updated: 2025/04/02 17:21:53 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parse.h"
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

void	free_all_data(t_data *data)
{
	if (data->args_list)
		free_args_list(&(data->args_list));
}

void	free_args_list(t_args_list **args_list)
{
	t_args_list	*tmp;
	t_args_list	*current;

	if (!args_list || !(*args_list))
		return ;
	current = *args_list;
	while (current)
	{
		tmp = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = tmp;
	}
	*args_list = NULL;
}

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	ft_error(char *str)
{
	perror(str);
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
	printf("Liste en sens inverse :\n");
	while (tail)
	{
		printf("%s -> ", tail->content);
		tail = tail->prev;
	}
	printf("NULL\n");
}
