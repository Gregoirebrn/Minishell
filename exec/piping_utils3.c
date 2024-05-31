/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:44:44 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/27 17:24:10 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	free_pipe(int **fd, t_head *head)
{
	size_t numb;
	size_t i;

	numb = cmdlen(head->cmd);
	i = 0;
	while (i < numb)
	{
		if (fd[i][1] != 0)
			close(fd[i][1]);
		if (fd[i][0] != 0)
			close(fd[i][0]);
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	fail_malloc(int **fd, size_t i)
{
	while (i-- > 0)
		free(fd[i]);
}

int	open_the_pipe(int **fd, t_head *head)
{
	size_t	numb;
	size_t	i;

	numb = cmdlen(head->cmd);
	if (numb == 1)
		return 0;
	i = 0;
	while (i < numb - 1)
	{
		fd[i] = calloc(sizeof (int *), 2);
		if (!fd[i])
			return (fail_malloc(fd, i), 1);
		i++;
	}
	i = 0;
	while (i < numb - 1)
	{
		if (pipe(fd[i]) == -1)
		{
			perror("pipe");
			free_pipe(fd, head);
			ft_free_all(head);
			exit (1);
		}
		i--;
	}
	return 0;
}

void	redir_with_fd(int **fd, t_cmd *copy, int x)
{
	if (copy->prev != NULL)
		fd[x][0] = fd[x - 1][0];
	if (copy->next != NULL)
		fd[x][1] = fd[x - 1][1];
}

void	dup_of_fd(int fd[2], t_cmd *copy)
{
	if (copy->prev != NULL)
	{
		if (dup2(fd[0], 0) < 0)
			return (perror("dup2first"));
		close(fd[0]);
	}
	else
		fd[0] = 0;
	if (copy->next != NULL)
	{
		if (dup2(fd[1], 1) < 0)
			return (perror("dup2sec"));
		close(fd[1]);
	}
	else
		fd[1] = 1;
}