/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:34:19 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/02 20:32:56 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	exec_shell(char **arg, char *str, char **env)
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
		ft_free(cmd);
	}
	if (!(access(arg[0], F_OK)) && !(access(arg[0], X_OK)))
		execve(arg[0], arg, env);
	exec_error_exit(arg, str, env, path);
}

int	no_fork_cmd(t_head *head, t_cmd *copy, char *str)
{
	if (!str || str[0] == 0)
		return (0);
	if (ft_strcmp(str, "cd") == 0)
		return (ft_cd(head), 0);
	if ((ft_strcmp(str, "export") == 0) && copy->arg[1] != NULL)
		return (ft_export(head), 0);
	if (ft_strcmp(str, "unset") == 0)
		return (ft_unset(head), 0);
	if (ft_strcmp(str, "exit") == 0 && (!copy->next && !copy->prev))
		return (ft_exit(head), 0);
	return (3);
}

int	exec_shell_malloc(t_head *head, t_cmd *copy, t_fnp *fnp)
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
		no_path_to_hapiness(head, env, tab);
	free_fnp(head, fnp);
	ft_free_all(head);
	exec_shell(tab, path, env);
	return (0);
}

int	find_cmd(t_head *head, t_cmd *copy, t_fnp *fnp, int x)
{
	int		fd[2];

	if (no_fork_cmd(head, copy, copy->arg[0]) == 0)
		return (fnp->pid[x] = 0, 0);
	fnp->pid[x] = fork();
	if (fnp->pid[x] < 0)
		ft_exit(head);
	if (fnp->pid[x] != 0)
		return (0);
	sig_main(head, 1);
	if (redir_with_fd(fd, fnp->pipe, copy, x))
		return (close_pipe(head, fnp->pipe), exit_free(head, 1), 2);
	close_pipe(head, fnp->pipe);
	if (ft_strcmp(copy->arg[0], "echo") == 0)
		return (ft_echo(head, copy), 1);
	if (ft_strcmp(copy->arg[0], "env") == 0)
		return (ft_env(head), 1);
	if (ft_strcmp(copy->arg[0], "pwd") == 0)
		return (ft_pwd(head), 1);
	if (ft_strcmp(copy->arg[0], "export") == 0)
		return (ft_export(head));
	if (ft_strcmp(copy->arg[0], "exit") == 0)
		return (ft_exit(head), 0);
	return (exec_shell_malloc(head, copy, fnp));
}

int	executable(t_head *head)
{
	t_cmd	*copy;
	int		x;

	x = 0;
	malloc_fnp(head);
	open_the_pipe(head->fnp->pipe, head);
	copy = head->cmd;
	while (copy != NULL)
	{
		find_cmd(head, copy, head->fnp, x);
		copy = copy->next;
		x++;
	}
	close_pipe(head, head->fnp->pipe);
	wait_for_all(head->fnp->pid, x);
	free_fnp(head, head->fnp);
	return (0);
}
