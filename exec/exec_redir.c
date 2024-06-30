/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:44:44 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/28 14:05:23 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	fail_malloc(t_head *head, int **fd, size_t i)
{
	while (i-- > 0)
		free(fd[i]);
	free(head->fnp->pid);
	free(head->fnp->pipe);
	free(head->fnp);
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
			return (fail_malloc(head, pipe, i), 1);
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
	if ((redir->type == 4 && redir->fd == -1) || redir->type == 3)
		redir->fd = open(redir->arg, O_RDONLY);
	if (redir->fd == -1)
		return (perror(redir->arg), 2);
	return (0);
}

int	open_redir(t_cmd *copy, int fd[2])
{
	t_redir	*parser;

	fd[1] = 1;
	fd[0] = 0;
	parser = copy->redir;
	while (parser)
	{
		if (open_files(parser))
			return (2);
		if (parser->type == 1 || parser->type == 2)
			fd[1] = parser->fd;
		if (parser->type == 3 || parser->type == 4)
			fd[0] = parser->fd;
		parser = parser->next;
	}
	return (0);
}
