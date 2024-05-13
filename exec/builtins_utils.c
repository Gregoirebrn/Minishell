/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:40:46 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/13 17:25:24 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

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

void	rem_env(t_env **env, void *ref, int (*cmp)(char *, const char *))
{
	t_env	*remove;
	t_env	*current;

	current = *env;
	while (current && current->next)
	{
		if ((*cmp)(current->next->name, ref) == 0)
		{
			remove = current->next;
			current->next = current->next->next;
			free(remove);
		}
		current = current->next;
	}
	current = *env;
	if (current && (*cmp)(current->name, ref) == 0)
	{
		*env = current->next;
		free(current);
	}
}

void	ft_env(t_head *head)
{
	t_env	*copy;

	copy = head->env;
	while (copy && copy->next != NULL)
	{
		printf("%s%s\n", copy->name, copy->value);
		copy = copy->next;
	}
	if (copy)
		printf("%s%s\n", copy->name, copy->value);
}
