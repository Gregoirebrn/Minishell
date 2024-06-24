/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:35:38 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/24 19:06:38 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cd_back_trim(char *str)
{
	char	*ret;
	int		i;
	int		x;

	i = 0;
	while (str && str[i])
		i++;
	while (str && str[i] != '/')
		i--;
	ret = malloc(sizeof(char) * (i + 1));
	x = -1;
	while (++x < i)
		ret[x] = str[x];
	ret[x] = 0;
	return (ret);
}

void	cd_back_error(t_head *head, char *old_pwd, char *new_pwd)
{
	DIR	*ptr_dir;

	g_error = 1;
	ptr_dir = opendir(head->cmd->arg[1]);
	write(2, "bash: cd: ", 10);
	perror(head->cmd->arg[1]);
	closedir(ptr_dir);
	free(old_pwd);
	free(new_pwd);
}

void	cd_back(t_head *head)
{
	int		err;
	char	*old_pwd;
	char	*pwd;
	char	*new_pwd;

	pwd = value_of_name(head->env, "PWD");
	old_pwd = ft_strdup(pwd);
	new_pwd = cd_back_trim(pwd);
	err = chdir(new_pwd);
	if (err != 0)
	{
		cd_back_error(head, old_pwd, new_pwd);
		return ;
	}
	replace_value(head, old_pwd, "OLDPWD");
	replace_value(head, new_pwd, "PWD");
}

char	*cd_tild_trim(t_head *head)
{
	char	*path;
	char	*pwd;
	int		i;
	int		x;

	pwd = value_of_name(head->env, "PWD");
	if (!pwd)
		return (NULL);
	i = 0;
	if (ft_strncmp("/home/", pwd, 5) == 0)
		i = 6;
	while (pwd[i] && pwd[i] != '/')
		i++;
	if (i < 6 || pwd[i] != '/')
		return (NULL);
	i++;
	path = malloc(sizeof(char) * i + 1);
	x = -1;
	while (i > ++x)
		path[x] = pwd[x];
	return (path[x] = '\0', path);
}

int	cd_tild(t_head *head)
{
	int		err;
	char	*old_pwd;
	char	*pwd;
	char	*new_pwd;

	pwd = value_of_name(head->env, "PWD");
	if (!pwd)
		return (write(2, "bash: cd: ~/: No such file or directory\n", 40), 2);
	old_pwd = ft_strdup(pwd);
	if (!old_pwd)
		return (2);
	new_pwd = cd_tild_trim(head);
	if (!new_pwd)
		return (free(old_pwd), 2);
	err = chdir(new_pwd);
	if (err != 0)
	{
		cd_back_error(head, old_pwd, new_pwd);
		return (2);
	}
	replace_value(head, old_pwd, "OLDPWD");
	replace_value(head, new_pwd, "PWD");
	return (0);
}
