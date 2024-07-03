/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:49:11 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/03 18:42:01 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//tild
//minus

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
	get_path(&old);
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
		return (cd_back_trim());
	if (0 == ft_strcmp(head->cmd->arg[1], "~/")
		|| 0 == ft_strcmp(head->cmd->arg[1], "~"))
		return (cd_tild_trim(head));
	if (0 == ft_strcmp(head->cmd->arg[1], "-"))
		return (cd_find_var(head, "OLDPWD"));
	get_path(&new);
	new = ft_strcat(new, head->cmd->arg[1]);
	if (!new)
		return (write(2, "Crash of Malloc\n", 16), ft_free_all(head), NULL);
	return (new);
}

int	replace_value(t_head *head, char *value, char *replace)
{
	t_env	*copy;

	copy = head->env;
	while (copy->next != NULL)
	{
		if (ft_strcmp(copy->name, replace) == 0)
		{
			free(copy->value);
			copy->value = value;
			return (0);
		}
		copy = copy->next;
	}
	return (1);
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

char	*ft_strcat(char *path, char *dir)
{
	char	*dest;
	size_t	i;
	size_t	x;

	dest = ft_calloc(sizeof (char), (ft_strlen(dir) + ft_strlen(path) + 2));
	if (dest == NULL)
		return (dest);
	i = 0;
	while (path && path[i])
	{
		dest[i] = path[i];
		i++;
	}
	x = 0;
	dest[i++] = '/';
	while (dir && dir[x])
	{
		dest[i] = dir[x];
		i++;
		x++;
	}
	dest[i] = '\0';
	free(path);
	return (dest);
}
