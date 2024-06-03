/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:44:44 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/03 17:26:58 by grebrune         ###   ########.fr       */
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
	return 0;
}

void	redir_with_fd(int fd[2], int **pipe, t_cmd *copy, int x)
{
	fd[0] = 0;
	fd[1] = 1;
	if (fd[0] == 0 && copy->prev != NULL)
		fd[0] = pipe[x - 1][0];
	if (fd[1] == 1 && copy->next != NULL)
		fd[1] = pipe[x][1];
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
}
//
//{
//	int		res[2] = 0;
//
//	if (s_cmd->fd_f[0] == 0 && s_cmd->prev)
//		s_cmd->fd_f[0] = args->pipe[id - 1][0];
//	if (s_cmd->fd_f[1] == 1 && s_cmd->next)
//		s_cmd->fd_f[1] = args->pipe[id][1];
//
//	if (s_cmd->fd_f[0] != 0)
//		res[0] = dup2(s_cmd->fd_f[0], STDIN_FILENO);
//	if (s_cmd->fd_f[1] != 1 && res[0] != -1)
//		res[1] = dup2(s_cmd->fd_f[1], STDOUT_FILENO);
//
//	if (s_cmd->file)
//		_close_file(args, s_cmd->fd_f, id);
//	_close_pipe(args);
//	if (res[0] == -1 || res[1] == -1)
//		_exit_failure(args);
//	return (1);
//}