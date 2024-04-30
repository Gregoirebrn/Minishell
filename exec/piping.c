/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:34:19 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/30 18:51:02 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

//remplace strncmp par strcmp
int	our_cmd(t_head *head, char *str)
{
	if (ft_strcmp(str, "echo"))
		return (ft_echo(head), 0);
	if (ft_strncmp(str, "cd", ft_strlen(str)))
	{
		if (ft_cd(head) == 2)
		exit(404);
	}
	if (ft_strncmp(str, "pwd", ft_strlen(str)))
		return (ft_pwd(), 0);
	if (ft_strncmp(str, "export", ft_strlen(str)))
		return (ft_export(head), 0);
	if (ft_strncmp(str, "unset", ft_strlen(str)))
		return (ft_unset(head), 0);
	if (ft_strncmp(str, "env", ft_strlen(str)))
		return (ft_env(head), 0);
	if (ft_strncmp(str, "exit", ft_strlen(str)))
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

void	make_child(t_head *head, t_cmd *copy)
{
	int		pid;
	int		fd[2];
	char	**env;
	char	**tab;
	char	*str;

	if (pid == 0)
	{
		if (copy->next)
			dup2(fd[1], 1);
		if (copy->prev)
			dup2(fd[0], 0);
		env = make_env(head->env);
		tab = make_arg(head->cmd);
		str = find_path(head);
		free_all(head);
		close(fd[0]);
		close(fd[1]);
		there_cmd(make_arg(head->cmd), find_path(head), make_env(head->env));
	}
}

int		executable(t_head *head)
{
	t_cmd	*copy;
	int		**fd;
	int		x;
	pid_t	*pid;

	x = 0;
	fd = malloc(sizeof(int *) * len_struct(head->cmd));
	pid = malloc(sizeof(int) * len_struct(head->cmd));
	copy = head->cmd;
	while (copy->arg)
	{
		if (pipe(fd[x]) == -1)
			return (perror("pipe"), free_all(head));
		pid[x] = fork();
		if (pid < 0)
		{
			close(fd[0]);
			close(fd[1]);
			return (perror("fork"), free_all);
		}
		if (our_cmd(head, head->cmd->arg[0]) == 1)
			make_child(head, head->cmd->arg[0], copy);
		copy = copy->next;
		x++;
	}
	wait_for_all(pid, x);
}