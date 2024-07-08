/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:31:24 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/09 01:14:30 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

char	*find_path(t_head *head)
{
	t_env	*copy;
	char	*path;

	copy = head->env;
	while (copy)
	{
		if (ft_strcmp("PATH", copy->name) == 0)
		{
			path = ft_strdup(copy->value);
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

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
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
	if (size == 0)
		return (NULL);
	tab = malloc(sizeof (char *) * (size + 1));
	if (tab == NULL)
		return (NULL);
	copy = env;
	i = 0;
	while (i < size)
	{
		tab[i] = join_with_char(copy->name, copy->value, '=');
		if (!tab[i])
			return (ft_splitdestroy(tab), NULL);
		i++;
		copy = copy->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	no_path_to_hapiness(t_head *head, char **env, char **tab, t_cmd *copy)
{
	char	*exec;

	exec = ft_strdup(copy->arg[0]);
	if (!exec)
		exec_error_exit(tab, env, NULL);
	free_fnp(head, head->fnp);
	ft_free_all(head);
	if (!(access(exec, F_OK)) && !(access(exec, X_OK)))
		execve(exec, tab, env);
	perror(exec);
	free_tab(env);
	free_tab(tab);
	ft_free(exec);
	if (errno == EACCES)
		exit (126);
	else
		exit (127);
}

void	free_malloc_fnp(t_head *head, int to_free)
{
	if (to_free > 1)
		free(head->fnp->pid);
	if (to_free > 0)
		free(head->fnp);
	ft_free_all(head);
	exit (0);
}
