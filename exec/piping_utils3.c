/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:44:44 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/13 14:56:08 by grebrune         ###   ########.fr       */
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

int	open_the_pipe(int **pipe, t_head *head)
{
	size_t	numb;
	size_t	i;

	numb = cmdlen(head->cmd);
	if (numb == 1)
		return (0);
	i = 0;
	while (i < numb)
	{
		pipe[i] = malloc(sizeof(int) * 2);
		if (!pipe[i])
			return (fail_malloc(pipe, i), 1);
		i++;
	}
	fill_pipe(numb, pipe, head);
	return (0);
}

int	open_files(t_redir *redir)
{
	if (redir->type == 1)
		redir->fd = open(redir->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->type == 2)
		redir->fd = open(redir->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->type == 3 || redir->type == 4)
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
