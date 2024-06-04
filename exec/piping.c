/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:34:19 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/04 17:26:28 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"


void	there_cmd(char **arg, char *str, char **env)
{
	char	**path;
	int		i;
	char	*cmd;

	path = ft_split(str, ':');
	i = 0;
	while (path[i])
	{
		cmd = join_with_char(path[i], arg[0], '/');
		if (!(access(cmd, F_OK)) && !(access(cmd, X_OK)))
			execve(cmd, arg, env);
		i++;
	}
	perror("execve");
	exit (2);
}

int		no_fork_cmd(t_head *head, t_cmd *copy, char *str, int fd[2])
{
	if (ft_strcmp(str, "cd") == 0)
		return (ft_cd(head));
	if ((ft_strcmp(str, "export") == 0) && copy->arg[1] != NULL)
		return (ft_export(head, fd), 0);
	if (ft_strcmp(str, "unset") == 0)
		return (ft_unset(head), 0);
	if (ft_strcmp(str, "exit") == 0)
		return (ft_exit(head), 0);
	return (3);
}

int		exec_shell(t_head *head, t_cmd *copy)
{
	char	**env;
	char	**tab;
	char	*path;

	env = make_env(head->env);
	tab = make_arg(copy);
	if (!env || !tab)
		return (ft_free_all(head), 1);
	path = find_path(head);
	ft_free_all(head);
	there_cmd(tab, path, env);
	return (0);
}

int		find_cmd(t_head *head, t_cmd *copy, int **pipes, int x)
{
	int		pid;
	int		fd[2];

	if (no_fork_cmd(head, copy, copy->arg[0], fd) == 0)
		return (0);
	pid = fork();
	if (pid < 0)
		ft_exit(head);
	if (pid == 0)
	{
		redir_with_fd(fd, pipes, copy, x);
		close_pipe(head, pipes);
		if (ft_strcmp(copy->arg[0], "echo") == 0)
			return (ft_echo(head, copy, fd), 1);
		if (ft_strcmp(copy->arg[0], "env") == 0)
			return (ft_env(head), 1);
		if (ft_strcmp(copy->arg[0], "pwd") == 0)
			return (ft_pwd(fd), 1);
		if (ft_strcmp(copy->arg[0], "export") == 0)
			return (ft_export(head, fd));
		return (exec_shell(head, copy));
	}
	return (pid);
}

int		executable(t_head *head)
{
	t_cmd	*copy;
	int		**pipes;
	int		x;
	int		*pid;

	x = 0;
	pid = malloc(sizeof(int) * cmdlen(head->cmd));
	pipes = malloc(sizeof(int) * cmdlen(head->cmd));
	open_the_pipe(pipes, head);
	copy = head->cmd;
	while (copy != NULL)
	{
		pid[x] = find_cmd(head, copy, pipes, x);
		printf("pid[%d] = %d\n", x, pid[x]);
		copy = copy->next;
		x++;
	}
	close_pipe(head, pipes);
	wait_for_all(pid, x);
	return (0);
}
