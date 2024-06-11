/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:44:44 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/11 18:14:15 by grebrune         ###   ########.fr       */
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

int	open_files(t_redir *redir)
{
	if (redir->type == 1)
		redir->fd = open(redir->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->type == 2)
		redir->fd = open(redir->arg, O_RDONLY);
	if (redir->type == 3)
		redir->fd = open(redir->arg, O_RDONLY);
	if (redir->type == 4)
		redir->fd = open(redir->arg, O_RDONLY);
	if (redir->fd == -1)
		return (perror(redir->arg), 2);
	return (0);
}

int	open_redir(t_cmd *copy, int fd[2])
{
	fd[1] = 1;
	fd[0] = 0;
	if (!copy->redir)
		return (0);
	if (open_files(copy->redir))
		return (2);
	if (copy->redir->type == 1 || copy->redir->type == 2)
		fd[1] = copy->redir->fd;
	if (copy->redir->type == 3 || copy->redir->type == 4)
		fd[0] = copy->redir->fd;
	return (0);
}

int	redir_with_fd(int fd[2], int **pipe, t_cmd *copy, int x)
{
	if (open_redir(copy, fd))
		return (2);
	if (fd[0] != 0 && copy->prev)
		fd[0] = pipe[x - 1][0];
	if (fd[1] != 1 && copy->next)
		fd[1] = pipe[x][1];
	if (fd[0] != 0 && copy->prev)
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("dup2"), 2);
	}
	if ((fd[1] != 1 && copy->next) || copy->redir)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			return (perror("dup2"), 2);
	}
	return (0);
}

void	close_pipe(t_head *head, int **fd)
{
	size_t	i;
	size_t	nbr_cmd;

	i = 0;
	nbr_cmd = cmdlen(head->cmd);
	while (i < nbr_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}
