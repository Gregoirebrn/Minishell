/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:30:25 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/05 16:09:27 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	ft_echo(t_head *head, t_cmd *copy, int fd[2])
{
	int		i;
	int		n;

	i = 1;
	n = 0;
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

void	ft_pwd(t_head *head)
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
	ft_free_all(head);
	exit(0);
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
	if (head->cmd->arg[1])
	{
		get_path(&str);
		str = ft_strcat(str, head->cmd->arg[1]);
	}
	else
	{
		cd_no_arg(head, &str);
		if (!str)
			return (printf("bash: cd: HOME not set\n"), 2);
	}
	if (str == NULL)
		return (printf("Crash of Malloc\n"), 2);
	get_path(&old_pwd);
	err = chdir(str);
	if (err == 0)
		replace_value(head, str, "PWD");
	if (err != 0)
		return (write(1, "bash: cd: ", 10), perror(head->cmd->arg[1]), 2);
	replace_value(head, old_pwd, "OLDPWD");
	return (0);
}

int		ft_export(t_head *head)
{
	t_env	*c_env;

	c_env = head->env;
	if (head->cmd->arg[1] == NULL)
		ex_no_args(head);
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

	if (head->cmd->next || !head->cmd->arg[1])
		return ;
	rem_env(&head->env, head->cmd->arg[1], &ft_strcmp);
}
