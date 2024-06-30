/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:31:24 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/26 21:44:03 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

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
		copy = copy->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	no_path_to_hapiness(t_head *head, char **env, char **tab)
{
	if (!(access(head->cmd->arg[0], F_OK))
		&& !(access(head->cmd->arg[0], X_OK)))
		execve(head->cmd->arg[0], head->cmd->arg, env);
	perror(head->cmd->arg[0]);
	free_tab(env);
	free_tab(tab);
	free_fnp(head, head->fnp);
	ft_free_all(head);
	exit (127);
}
