/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:30:25 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/21 15:27:45 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	ft_echo(t_head *head, int fd[2])
{
	t_cmd	*copy;
	int		i;
	int		n;

	i = 1;
	n = 0;
	copy = head->cmd;
	if (!copy->arg[1])
	{
		printf("\n");
		return ;
	}
	if (0 == ft_strcmp(copy->arg[i], "-n"))
	{
		i++;
		n++;
	}
	if (ft_strcmp("$?", copy->arg[i]) == 0)
	{
		printf("%d\n", g_error);
		g_error = 0;
		return ;
	}
	print_tab(copy->arg, i, n, fd);
	ft_free_all(head);
	exit(0);
}

void	ft_pwd(void)
{
	int		err;
	char	*str;

	str = NULL;
	err = get_path(&str);
	if (err == 2)
	{
		write(1, "bash: pwd: ", 10);
		perror(str);
	}
	printf("%s\n", str);
	free(str);
}

int	ft_cd(t_head *head)

{
	int		err;
	char	*str;
	char	*old_pwd;

	old_pwd = NULL;
	str = NULL;
	if (head->cmd->next != NULL)
		return (1);
	if (head->cmd->arg[1] && head->cmd->arg[2])
		return (printf("Only one argument is taken by cd\n"), 2);
	get_path(&str);
	str = ft_strcat(str, head->cmd->arg[1]);
	if (str == NULL)
		return (printf("Crash of Malloc\n"), 2);
	get_path(&old_pwd);
	err = chdir(str);
	free(str);
	if (err != 0)
		return (write(1, "bash: cd: ", 10), perror(head->cmd->arg[1]), 2);
	change_old_pwd(head, old_pwd);
	return (0);
}

int	ft_export(t_head *head)
{
	t_env	*c_env;

	c_env = head->env;
	if (head->cmd->arg[1] == NULL)
		return (ex_no_args(head));
	if (head->cmd->next != NULL)
		return (3);
	while (c_env->next != NULL)
	{
		if (0 == strcmp(c_env->name, head->cmd->arg[1]))
		{
			replace_var(&c_env->value, head->cmd->arg[2]);
			return (0);
		}
		c_env = c_env->next;
	}
	return (add_env(head, head->cmd->arg[1], head->cmd->arg[2]));
}

void	ft_unset(t_head *head)
{
	char	*ref;

	if (!head->cmd->next || !head->cmd->arg[1])
		return ;
	ref = ft_strjoin(head->cmd->arg[1], "=");
	rem_env(&head->env, ref, &ft_strcmp);
	free(ref);
}
