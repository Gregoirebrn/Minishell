/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:30:25 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/12 18:02:16 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	ft_echo(t_head *head, t_cmd *copy)
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
		printf("%d", g_error);
		if (n == 0)
			printf("\n");
		exit(0);
	}
	print_tab(copy->arg, i, n);
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
	DIR		*ptr_dir;

	old_pwd = NULL;
	str = NULL;
	if (head->cmd->next != NULL)
		return (1);
	if (ft_cd_bis(head, &str) == 2)
		return (2);
	get_path(&old_pwd);
	err = chdir(str);
	if (err != 0)
	{
		ptr_dir = opendir(head->cmd->arg[1]);
		return (write(2, "bash: cd: ", 10), perror(head->cmd->arg[1]), 1);
		closedir(ptr_dir);
	}
	replace_value(head, str, "PWD");
	replace_value(head, old_pwd, "OLDPWD");
	return (0);
}

int	ft_export(t_head *head)
{
	t_env	*c_env;

	c_env = head->env;
	if (head->cmd->arg[1] == NULL)
		ex_no_args(head);
	if (head->cmd->next != NULL)
		return (3);
	while (c_env)
	{
		if (0 == ft_strcmp_until(c_env->name, head->cmd->arg[1]))
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
