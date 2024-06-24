/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:49:11 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/24 18:12:56 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		g_error = 1;
		ptr_dir = opendir(head->cmd->arg[1]);
		return (free(old_pwd), free(str), \
				write(2, "bash: cd: ", 10), perror(head->cmd->arg[1]), 1);
		closedir(ptr_dir);
	}
	replace_value(head, str, "PWD");
	replace_value(head, old_pwd, "OLDPWD");
	return (0);
}

int	ft_cd_bis(t_head *head, char **str)
{
	if (head->cmd->arg[1] && head->cmd->arg[2])
		return (write(2, "bash: cd: too many arguments\n", 29), 2);
	if (head->cmd->arg[1])
	{
		if (0 == ft_strcmp(head->cmd->arg[1], "../")
			|| 0 == ft_strcmp(head->cmd->arg[1], ".."))
			return (cd_back(head), 2);
		if (0 == ft_strcmp(head->cmd->arg[1], "~/"))
			return (cd_tild(head), 2);
		get_path(str);
		*str = ft_strcat(*str, head->cmd->arg[1]);
		if (!*str)
			return (ft_free_all(head), exit(1), 1);
	}
	else
	{
		cd_no_arg(head, str);
		if (!*str)
			return (write(2, "bash: cd: HOME not set\n", 23), 2);
	}
	if (*str == NULL)
		return (write(2, "Crash of Malloc\n", 16), 2);
	return (0);
}

void	replace_value(t_head *head, char *value, char *replace)
{
	t_env	*copy;

	copy = head->env;
	while (copy->next != NULL)
	{
		if (ft_strcmp(copy->name, replace) == 0)
		{
			free(copy->value);
			copy->value = value;
		}
		copy = copy->next;
	}
}

void	cd_no_arg(t_head *head, char **str)
{
	t_env	*env;

	env = head->env;
	while (env)
	{
		if (ft_strcmp(env->name, "HOME") == 0)
		{
			*str = env->value;
			break ;
		}
		env = env->next;
	}
}

char	*ft_strcat(char *path, char *dir)
{
	char	*dest;
	size_t	i;
	size_t	x;

	dest = malloc(sizeof (char) * (ft_strlen(dir) + ft_strlen(path) + 2));
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
