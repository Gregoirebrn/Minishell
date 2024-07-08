/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:13:12 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/08 18:40:36 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_free(t_head*head, int status)
{
	free_fnp(head, head->fnp);
	ft_free_all(head);
	exit (status);
}

void	new_pwd(t_head *head, char *value, char *name)
{
	t_env	*new;
	t_env	*copy;

	copy = head->env;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return ;
	while (copy && copy->next)
		copy = copy->next;
	new_var_bis(copy, head, new);
	new->next = NULL;
	new->name = ft_strdup(name);
	if (!new->name)
		return ;
	new->value = ft_strdup(value);
	if (!new->value)
		return ;
	return ;
}

int	replace_value(t_head *head, char *value, char *replace)
{
	t_env	*copy;

	copy = head->env;
	while (copy)
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

char	*cat_of_tild(t_head *head, char *str)
{
	size_t	i;
	size_t	x;
	char	*new;
	char	*home;

	i = 0;
	home = cd_find_var(head, "HOME");
	if (!home)
		return (NULL);
	i = ft_strlen(str) - 1;
	x = ft_strlen(home);
	new = ft_calloc(sizeof (char), x + i + 1);
	if (!new)
		return (free(home), NULL);
	i = -1;
	while (home[++i])
		new[i] = home[i];
	x = 1;
	while (str[x])
		new[i++] = str[x++];
	new[i] = '\0';
	return (free(home), new);
}
