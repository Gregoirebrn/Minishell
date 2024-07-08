/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:49:11 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/08 18:29:32 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_error(t_head *head)
{
	if (head->cmd->next || (head->cmd->arg[1] && head->cmd->arg[1][0] == 0))
		return (1);
	if (head->cmd->arg[1] && head->cmd->arg[2])
		return (write(2, "bash: cd: too many arguments\n", 29), g_error = 1, 1);
	return (0);
}

void	cd_rep_or_new(t_head *head, char *n_pwd, char *old_pwd)
{
	if (replace_value(head, n_pwd, "PWD"))
	{
		new_pwd(head, n_pwd, "PWD");
		free(n_pwd);
	}
	if (replace_value(head, old_pwd, "OLDPWD"))
	{
		new_pwd(head, old_pwd, "OLDPWD");
		free(old_pwd);
	}
}

int	ft_cd(t_head *head)
{
	int		err;
	char	*new;
	char	*old;

	old = NULL;
	if (cd_error(head))
		return (1);
	new = cd_relative(head);
	if (!new)
		return (2);
	err = get_path(&old);
	if (err == 2)
		exit_free(head, 0);
	err = chdir(new);
	if (err != 0)
		return (cd_chdir_error(head, old, new), 1);
	cd_rep_or_new(head, new, old);
	return (0);
}

char	*cd_relative(t_head *head)
{
	char	*new;

	new = NULL;
	if (!head->cmd->arg[1])
		return (cd_find_var(head, "HOME"));
	if (0 == ft_strcmp(head->cmd->arg[1], "../")
		|| 0 == ft_strcmp(head->cmd->arg[1], ".."))
		return (cd_back_trim(head));
	if (0 == ft_strcmp(head->cmd->arg[1], "~/")
		|| 0 == ft_strcmp(head->cmd->arg[1], "~"))
		return (cd_tild_trim(head));
	if (0 == ft_strcmp(head->cmd->arg[1], "-"))
		return (cd_find_var(head, "OLDPWD"));
	if (!ft_strncmp(head->cmd->arg[1], "~/", 2))
		return (cat_of_tild(head, head->cmd->arg[1]));
	if (!ft_strncmp(head->cmd->arg[1], "/home", 5))
		return (ft_strdup(head->cmd->arg[1]));
	get_path(&new);
	new = cd_cat_backslash(new, head->cmd->arg[1]);
	if (!new)
		return (write(2, "Crash of Malloc\n", 16), NULL);
	return (new);
}

char	*cd_find_var(t_head *head, char *name)
{
	t_env	*env;
	char	*str;

	str = NULL;
	env = head->env;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			str = ft_strdup(env->value);
			if (!str)
				return (write(2, "Crash of Malloc\n", 16), NULL);
			break ;
		}
		env = env->next;
	}
	if (!str)
		return (cd_not_found(name), NULL);
	return (str);
}
