/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:51:28 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/08 14:20:38 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	wait_for_all(pid_t *pid, int x)
{
	int	i;

	i = 0;
	while (i < x)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free(pid);
}

size_t	envlen(t_env *base)
{
	size_t	size;
	t_env	*copy;

	copy = base;
	size = 0;
	if (copy != NULL)
		size++;
	while (copy->next != NULL)
	{
		size++;
		copy = copy->next;
	}
	return (size);
}

size_t	cmdlen(t_cmd *base)
{
	size_t	size;
	t_cmd	*copy;

	copy = base;
	size = 0;
	if (copy != NULL)
		size++;
	while (copy->next != NULL)
	{
		size++;
		copy = copy->next;
	}
	return (size);
}

char	**make_arg(t_cmd *cmd)
{
	char	**arg;
	int		x;

	x = 0;
	while (cmd->arg && cmd->arg[x])
		x++;
	arg = malloc(sizeof (char *) * (x + 1));
	if (arg == NULL)
		return (NULL);
	x = 0;
	while (cmd->arg && cmd->arg[x])
	{
		arg[x] = ft_strdup(cmd->arg[x]);
		x++;
	}
	arg[x] = NULL;
	return (arg);
}

void	ft_free_exec(int **fd, pid_t *pid, t_head *head)
{
	int	i;

	i = 0;
	while (head->cmd->next != NULL)
	{
		i++;
		head->cmd = head->cmd->next;
	}
	if (head->cmd != NULL)
		i++;
	while (--i > 0)
	{
		free(fd[i]);
		i--;
	}
		free(pid);
}