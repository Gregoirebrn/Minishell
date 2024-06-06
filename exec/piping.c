/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:34:19 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/06 12:39:13 by grebrune         ###   ########.fr       */
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
	g_error = 127;
	perror(arg[0]);
	exit (2);
}

int	no_fork_cmd(t_head *head, t_cmd *copy, char *str)
{
	if (ft_strcmp(str, "cd") == 0)
		return (ft_cd(head), 0);
	if ((ft_strcmp(str, "export") == 0) && copy->arg[1] != NULL)
		return (ft_export(head), 0);
	if (ft_strcmp(str, "unset") == 0)
		return (ft_unset(head), 0);
	if (ft_strcmp(str, "exit") == 0)
		return (ft_exit(head), 0);
	return (3);
}

int	exec_shell(t_head *head, t_cmd *copy)
{
	char	**env;
	char	**tab;
	char	*path;

	env = make_env(head->env);
	tab = make_arg(copy);
	if (!env || !tab)
	{
		if (!env)
			return (free(tab), ft_free_all(head), 1);
		else
			return (free(env), ft_free_all(head), 1);
	}
	path = find_path(head);
	if (!path)
		return (free(env), free(tab), ft_free_all(head), 1);
	ft_free_all(head);
	there_cmd(tab, path, env);
	return (0);
}

int	find_cmd(t_head *head, t_cmd *copy, int **pipes, int x)
{
	int		pid;
	int		fd[2];

	if (no_fork_cmd(head, copy, copy->arg[0]) == 0)
		return (0);
	pid = fork();
	if (pid < 0)
		ft_exit(head);
	if (pid == 0)
	{
		redir_with_fd(fd, pipes, copy, x);
		close_pipe(head, pipes);
		if (ft_strcmp(copy->arg[0], "echo") == 0)
			return (ft_echo(head, copy), 1);
		if (ft_strcmp(copy->arg[0], "env") == 0)
			return (ft_env(head), 1);
		if (ft_strcmp(copy->arg[0], "pwd") == 0)
			return (ft_pwd(head), 1);
		if (ft_strcmp(copy->arg[0], "export") == 0)
			return (ft_export(head));
		return (exec_shell(head, copy));
	}
	return (pid);
}

int	executable(t_head *head)
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
		copy = copy->next;
		x++;
	}
	close_pipe(head, pipes);
	wait_for_all(pid, x);
	return (0);
}
