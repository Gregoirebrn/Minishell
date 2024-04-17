/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:30:25 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/17 17:33:15 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// chaque arg[i] est a 1 ou 0 il faut savoir si la commande sera dans les arg ou pas
// les ecritures sont surement fausse il faudra se renseigner

void	ft_echo(t_head *head)
{
	t_cmd	*copy;
	int		i;

	i = 0;
	copy = head->cmd;
	while (copy->next != NULL)
	{
		if (i == 1 && ft_strncmp(copy->arg[i], "-n", ft_strlen(copy->arg[i])))
			i = -1;
		printf("%s ", copy->arg[i]);
		copy = copy->next;
		if (i > -1)
			i++;
	}
	if (copy != NULL && i != -1)
		printf("%s\n", copy->arg[i]);
	else
		printf("%s", copy->arg[i]);
}

int		get_path(char **str)
{
	size_t	size;

	size = 10;
	while (!*(str))
	{
		*str = getcwd(*(str), size);
		if (!*(str))
		{
			free(*(str));
			*(str) = NULL;
			if (errno != ERANGE)
				return (2);
		}
		size += 10;
	}
	return (0);
}

void	ft_pwd(void)
{
	int		err;
	char	*str;

	str = NULL;
	err = get_path(&str);
	if (err == 2)
		perror("Error from getcwd\n");
	printf("%s\n", str);
	free(str);
}

char	*ft_strcat(char *path, char *dir)
{
	char	*dest;
	size_t	i;
	size_t	x;

	dest = malloc(sizeof (char) * (strlen(dir) + strlen(path) + 2));
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

int	ft_cd(t_head *head)

{
	int		err;
	char	*str;
	int		len;

	str = NULL;
	get_path(&str);
	str = ft_strcat(str, head->cmd->arg[1]);
	if (dest == NULL)
		return (printf("Crash of Malloc\n"), 2);
	err = chdir(str);
	free(str);
	if (err != 0)
		return (perror("cd"), 2);
	return (0);
}
