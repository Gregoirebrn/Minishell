/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:51:28 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/26 19:11:13 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	wait_for_all(pid_t *pid, int x)
{
	int		i;
	int		wstatus[2];
	int		last;

	wstatus[1] = 0;
	wstatus[0] = 0;
	i = 0;
	while (i < x)
	{
		last = waitpid(0, &wstatus[0], 0);
		if (last == pid[x - 1])
			wstatus[1] = wstatus[0];
		i++;
	}
	if (WIFEXITED(wstatus[1]) == 0)
		g_error = 130;
	else
		g_error = WEXITSTATUS(wstatus[1]);
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

char	**redir_arg(t_cmd *cmd, int type)
{
	char	**arg;

	arg = malloc(sizeof (char *) * (3));
	if (arg == NULL)
		return (NULL);
	if (type == 1)
		arg[0] = ft_strdup("rm");
	else
		arg[0] = ft_strdup(cmd->arg[0]);
	arg[1] = ft_strdup("tmp");
	arg[2] = NULL;
	return (arg);
}

char	**make_arg(t_cmd *cmd)
{
	char	**arg;
	int		x;

	x = 0;
	if ((cmd->redir && cmd->redir->type == 4))
		return (redir_arg(cmd, 0));
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
