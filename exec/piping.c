/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:34:19 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/08 15:09:12 by grebrune         ###   ########.fr       */
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
		if (!(access(cmd, F_OK)))
			execve(cmd, arg, env);
		i++;
	}
	perror("execve");
	exit (2);
}

int		fork_proc_cmd(t_head *head, char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (ft_echo(head), 1);
	if (ft_strcmp(str, "env") == 0)
		return (ft_env(head), 1);
	if (ft_strcmp(str, "pwd") == 0)
		return (ft_pwd(), 1);
	if ((ft_strcmp(str, "export") == 0) && head->cmd->arg[1] != NULL)
		return (ft_export(head));
	return (3);
}

int		make_child(t_head *head, t_cmd *copy, int *fd)
{
	int		pid;
	char	**env;
	char	**tab;
	char	*str;

	pid = fork();
	if (pid == 0)
	{
		if (copy->next != NULL)
			dup2(fd[1], 1);
		if (copy->prev != NULL)
			dup2(fd[0], 0);
		if (fork_proc_cmd(head, head->cmd->arg[0]) == 1)
			return (0);
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

int		find_cmd(t_head *head, char *str, int *fd)
{
	if (ft_strcmp(str, "cd") == 0)
		return (ft_cd(head));
	if (ft_strcmp(str, "export") == 0)
		return (ft_export(head), 0);
	if (ft_strcmp(str, "unset") == 0)
		return (ft_unset(head), 0);
	if (ft_strcmp(str, "exit") == 0)
		return (ft_exit(head), 0);
	return (make_child(head, head->cmd, fd));
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
	while (copy->next != NULL)
	{
		if (pipe(fd[x]) == -1)
			return (perror("pipe"), ft_free_all(head), 1);
		find_cmd(head, head->cmd->arg[0], fd[x]);
		copy = copy->next;
		x++;
	}
	if (copy != NULL)
	{
		find_cmd(head, head->cmd->arg[0], fd[x]);
		x++;
	}
//	ft_free_exec(fd, pid, head);
//	wait_for_all(pid, x);
	return (0);
}
