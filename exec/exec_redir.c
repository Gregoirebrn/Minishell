/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:44:44 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/02 22:38:47 by grebrune         ###   ########.fr       */
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
	ft_free_all(head);
	exit(0);
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

int	open_files(t_redir *redir, int err_print)
{
	if (redir->type == 1)
		redir->fd = open(redir->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->type == 2)
		redir->fd = open(redir->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((redir->type == 4 && redir->fd == -1) || redir->type == 3)
		redir->fd = open(redir->arg, O_RDONLY);
	if (redir->fd == -1)
	{
		if (err_print == 0)
			perror(redir->arg);
		return (2);
	}
	return (0);
}

int	open_redir(t_cmd *copy, int fd[2])
{
	t_redir	*parser;
	t_cmd	*c_cmd;
	int		err_print;

	fd[1] = 1;
	fd[0] = 0;
	c_cmd = copy;
	err_print = 0;
	while (c_cmd)
	{
		parser = c_cmd->redir;
		while (parser)
		{
			if (open_files(parser, err_print))
				return (2);
			if (parser->type == 1 || parser->type == 2)
				fd[1] = parser->fd;
			if (parser->type == 3 || parser->type == 4)
				fd[0] = parser->fd;
			parser = parser->next;
		}
		c_cmd = c_cmd->next;
		err_print++;
	}
	return (0);
}
