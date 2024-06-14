/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:31:24 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/09 15:21:17 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

char	**path_value(t_head *head)
{
	t_head	*copy;

	copy = head;
	while (copy->env->next != NULL)
	{
		if (ft_strcmp(copy->env->name, "PATH") == 0)
		{
			return (ft_split(copy->env->value, ':'));
		}
		copy->env = copy->env->next;
	}
	return (NULL);
}

char	*find_path(t_head *head)
{
	t_env	*copy;
	char	*path;

	copy = head->env;
	while (copy->next != NULL)
	{
		if (ft_strcmp("PATH", copy->name) == 0)
		{
			path = strdup(copy->value);
			return (path);
		}
		copy = copy->next;
	}
	return (NULL);
}

char	*join_with_char(char const *s1, char const *s2, char c)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*str;

	len = strlen((char *)s1) + strlen((char *)s2);
	i = 0;
	str = malloc (sizeof(char) * (len + 2));
	if (str == NULL)
		return (str);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = c;
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str [i + j] = 0;
	return (str);
}

char	**make_env(t_env *env)
{
	t_env	*copy;
	char	**tab;
	size_t	size;
	size_t	i;

	size = envlen(env);
	tab = malloc(sizeof (char *) * (size + 1));
	if (tab == NULL)
		return (NULL);
	copy = env;
	i = 0;
	while (i < size)
	{
		tab[i] = join_with_char(copy->name, copy->value, '=');
		if (tab[i] == NULL)
			return (NULL);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
