/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:35:38 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/03 18:41:12 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cd_tild_trim(t_head *head)
{
	char	*pwd;
	char	*new;

	pwd = cd_find_var(head, "USER");
	if (!pwd)
		return (NULL);
	new = ft_strjoin("/home/", pwd);
	if (!new)
		return (free(pwd), write(2, "Crash of Malloc\n", 16), NULL);
	return (free(pwd), new);
}

char	*cd_back_trim(void)
{
	char	*pwd;
	char	*new;
	int		i;
	int		x;

	i = 0;
	pwd = NULL;
	get_path(&pwd);
	printf("--%s--\n", pwd);
	while (pwd && pwd[i])
		i++;
	while (pwd && pwd[i] != '/')
		i--;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (free(pwd), write(2, "Crash of Malloc\n", 16), NULL);
	x = 0;
	while (x < i)
	{
		new[x] = pwd[x];
		x++;
	}
	new[x] = 0;
	return (free(pwd), new);
}

void	cd_not_found(char *name)
{
	write(2, "bash: cd: ", 10);
	write(2, name, ft_strlen(name));
	write(2, " not set\n", 9);
}

void	cd_chdir_error(t_head *head, char *old_pwd, char *new_pwd)
{
	DIR	*ptr_dir;

	g_error = 1;
	ptr_dir = opendir(head->cmd->arg[1]);
	perror("bash: cd");
	closedir(ptr_dir);
	free(old_pwd);
	free(new_pwd);
}

char	*cd_cat_backslash(char *path, char *dir)
{
	char	*dest;
	size_t	i;
	size_t	x;

	dest = ft_calloc(sizeof (char), (ft_strlen(dir) + ft_strlen(path) + 2));
	if (!dest)
		return (NULL);
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
