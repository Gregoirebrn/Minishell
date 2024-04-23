/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:34:19 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/23 15:35:25 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	our_cmd(t_head *head, char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)))
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

void	our_cmd(t_head *head, char *str)
{
	{
		char	**path;
		char	*str;
		int		i;
		char	*cmd;

		str = find_path(head);
		path = ft_split(str, ':');
		i = 0;
		while (path[i])
		{
			cmd = join_with_char(path[i], head->cmd->arg[0], '/');
			if (!(access(cmd, F_OK)))
				execve(cmd, head->cmd->arg, make_env(head->env));
			i++;
		}
		perror("execve");
	}
}

void	find_cmd(t_head *head)
{
	if (our_cmd(head, head->cmd->arg[0]) == 1)
		return (other_cmd(head, head->cmd->arg[0]));
}

void	piping(t_head *head)
{
	if (head->cmd->next == NULL)
		return (find_cmd(head));
}