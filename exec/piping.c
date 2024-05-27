/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:34:19 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/27 13:58:12 by grebrune         ###   ########.fr       */
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

int		no_fork_cmd(t_head *head, t_cmd *copy, char *str)
{
	if (ft_strcmp(str, "cd") == 0)
		return (ft_cd(head));
	if ((ft_strcmp(str, "export") == 0) && copy->arg[1] != NULL)
		return (ft_export(head), 0);
	if (ft_strcmp(str, "unset") == 0)
		return (ft_unset(head), 0);
	if (ft_strcmp(str, "exit") == 0)
		return (ft_exit(head), 0);
	return (3);
}

int		exec_shell(t_head *head)
{
	char	**env;
	char	**tab;
	char	*path;

	env = make_env(head->env);
	tab = make_arg(head->cmd);
	if (!env || !tab)
		return (ft_free_all(head), 1);
	path = find_path(head);
	ft_free_all(head);
	there_cmd(tab, path, env);
	return (0);
}

int		find_cmd(t_head *head, t_cmd *copy, int fd[2], int pid)
{
	if (no_fork_cmd(head, copy, head->cmd->arg[0]) == 0)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		dup_of_fd(fd, copy);
		if (ft_strcmp(copy->arg[0], "echo") == 0)
			return (ft_echo(head, fd), 1);
		if (ft_strcmp(copy->arg[0], "env") == 0)
			return (ft_env(head), 1);
		if (ft_strcmp(copy->arg[0], "pwd") == 0)
			return (ft_pwd(), 1);
		if (ft_strcmp(copy->arg[0], "export") == 0)
			return (ft_export(head));
		return (exec_shell(head));
	}
	return (1);
}

int		executable(t_head *head)
{
	t_cmd	*copy;
	int		fd[2];
	int		x;
	int		*pid;

	x = 0;
	pid = malloc(sizeof(int) * cmdlen(head->cmd) + 1);
	copy = head->cmd;
	copy->next = NULL;
	while (copy != NULL)
	{
		if (pipe(fd) == -1)
			return (perror("pipe"), ft_free_all(head), 1);
		find_cmd(head, copy, fd, pid[x]);
		copy = copy->next;
		x++;
	}
	wait_for_all(pid, x);
	return (0);
}
