/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:51:28 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/02 21:16:03 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	wait_for_all(pid_t *pid, int x)
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
		if (last != -1 && last == pid[x - 1])
			wstatus[1] = wstatus[0];
		i++;
	}
	if (WIFSIGNALED(wstatus[1]) && WCOREDUMP(wstatus[1]))
	{
		write(2, "Quit (core dumped)\n", 19);
		g_error = 131;
	}
	else if (WIFSIGNALED(wstatus[1]))
		return (write(2, "\n", 1), g_error = 130, 0);
	if (WIFEXITED(wstatus[1]) && last != -1)
		g_error = WEXITSTATUS(wstatus[1]);
	return (0);
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
