/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:34:19 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/07 16:26:00 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int		our_cmd(t_head *head, char *str)
{
	if (ft_strcmp(str, "echo"))
		return (ft_echo(head), 0);
	if (ft_strcmp(str, "cd"))
	{
		if (ft_cd(head) == 2)
		exit(404);
	}
	if (ft_strcmp(str, "pwd"))
		return (ft_pwd(), 0);
	if (ft_strcmp(str, "export"))
		return (ft_export(head), 0);
	if (ft_strcmp(str, "unset"))
		return (ft_unset(head), 0);
	if (ft_strcmp(str, "env"))
		return (ft_env(head), 0);
	if (ft_strcmp(str, "exit"))
		return (ft_exit(head), 0);
	return (1);
}

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
		if (!(access(cmd, F_OK)))
			execve(cmd, arg, env);
		i++;
	}
	perror("execve");
	exit (2);
}

int		make_child(t_head *head, t_cmd *copy)
{
	int		pid;
	int		fd[2];
	char	**env;
	char	**tab;
	char	*str;

	pid = fork();
	if (pid == 0)
	{
		if (copy->next)
			dup2(fd[1], 1);
		if (copy->prev)
			dup2(fd[0], 0);
		env = make_env(head->env);
		tab = make_arg(head->cmd);
		if (!env || !tab)
			return (ft_free_all(head), 1);
		str = find_path(head);
		ft_free_all(head);
		close(fd[0]);
		close(fd[1]);
		there_cmd(tab, str, env);
	}
	return (0);
}

int		executable(t_head *head)
{
	t_cmd	*copy;
	int		**fd;
	int		x;
	pid_t	*pid;

	x = 0;
	fd = malloc(sizeof(int *) * cmdlen(head->cmd));
	pid = malloc(sizeof(int) * cmdlen(head->cmd));
	copy = head->cmd;
	while (copy->arg)
	{
		if (pipe(fd[x]) == -1)
			return (perror("pipe"), ft_free_all(head), 1);
		pid[x] = fork();
		if (pid < 0)
		{
			close(fd[x][0]);
			close(fd[x][1]);
			return (perror("fork"), ft_free_all(head), 2);
		}
		if (our_cmd(head, head->cmd->arg[0]) == 1)
		{
			if (make_child(head, copy))
				return (printf("Crash of Malloc"), ft_free_all(head), 1);
		}
		copy = copy->next;
		x++;
	}
	wait_for_all(pid, x);
	return (0);
}
