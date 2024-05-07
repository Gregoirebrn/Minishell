/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:30:25 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/25 12:50:54 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_head *head)
{
	t_cmd	*copy;
	int		i;

	i = 0;
	copy = head->cmd;
	while (copy->next != NULL)
	{
		if (i == 1 &&  0 == ft_strncmp(copy->arg[i], "-n", ft_strlen(copy->arg[i])))
			i = -1;
		printf("%s ", copy->arg[i]);
		copy = copy->next;
		if (i > -1)
			i++;
	}
	if (0 == ft_strncmp(copy->arg[i], "-n", ft_strlen(copy->arg[i])))
		printf("%s", copy->arg[i]);
	else
		printf("%s\n", copy->arg[i]);
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
	if (head->cmd->arg[1] && head->cmd->arg[2])
		return (printf("Only one argument is taken by cd\n"), 1);
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
	t_head	*copy;

	copy = head;
	if (!head->cmd->arg)
		return (ex_no_args(head));
	while (copy->env->name)
	{
		if (0 == strncmp(copy->env->name, copy->cmd->arg[0],
						 strlen(copy->cmd->arg[0])))
		{
			replace_var(&copy->env->value, copy->cmd->arg[1]);
			return (0);
		}
		copy->env = copy->env->next;
	}
	return (add_env(head, head->cmd->arg[0], head->cmd->arg[1]));
}

void	ft_unset(t_head *head)
{
	rem_env(&head->env, head->cmd->arg[1], &ft_strncmp);
}
