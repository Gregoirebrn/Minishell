/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:44:44 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/06 12:09:29 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	free_pipe(int **fd, t_head *head)
{
	size_t	numb;
	size_t	i;

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
		return (0);
	i = 0;
	while (i < numb)
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
		i++;
	}
	fd[i][1] = 1;
	return (0);
}

//void	open_redir(t_cmd *copy, int **pipe, int fd[2], int x)
//{
//	if (!copy->redir)
//		return;
//	if (copy->redir->type)
//}

void	redir_with_fd(int fd[2], int **pipe, t_cmd *copy, int x)
{
//	open_redir(copy, pipe, fd, x);
	if (copy->prev)
		fd[0] = pipe[x - 1][0];
	else
		fd[0] = 0;
	if (copy->next)
		fd[1] = pipe[x][1];
	else
		fd[1] = 1;
	if (fd[0] != 0 && copy->prev != NULL)
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("dup2first"));
	}
	if (fd[1] != 1 && copy->next != NULL)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			return (perror("dup2sec"));
	}
}

void	close_pipe(t_head *head, int **fd)
{
	size_t		i;
	size_t		nbr_cmd;

	i = 0;
	nbr_cmd = cmdlen(head->cmd);
	while (i < nbr_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}
