/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:04:21 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/08 14:51:55 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	change_old_pwd(t_head *head, char *old_pwd)
{
	t_env	*copy;

	copy = head->env;
	while (copy->next != NULL)
	{
		if (ft_strcmp(copy->name, "OLDPWD"))
		{
			free(copy->value);
			copy->value = old_pwd;
		}
		copy = copy->next;
	}
}

void	replace_var(char **arg, char *result)
{
	int		z;

	free(*(arg));
	*arg = calloc((strlen(result) + 1), sizeof (char));
	z = 0;
	while (result[z])
	{
		*(arg[z]) = result[z];
		z++;
	}
	*(arg[z]) = '\0';
}

int	ex_no_args(t_head *head)
{
	t_env	*copy;
	t_env	*big;
	t_env	*top;

	top = head->env;
	copy = top;
	while (!copy->next)
	{
		big = copy;
		while (!copy->next)
		{
			if (0 < ft_strcmp(big->name, copy->next->name))
			{
				if (0 < ft_strcmp(big->value, copy->next->name))
					big = copy;
			}
			copy = copy->next;
		}
		printf("declare -x %s=%s", big->name, big->value);
		big->prev->next = big->next;
		big->next->prev = big->prev;
		copy = top;
	}
	printf("declare -x %s=%s", copy->name, copy->value);
	return (0);
}

int		add_env(t_head *head, char *name, char *value)
{
	t_env	*new;
	t_env	*copy;

	copy = head->env;
	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	while (!copy->next)
		copy = copy->next;
	copy->next = new;
	new->prev = copy;
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	return (0);
}
