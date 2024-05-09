/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:04:21 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/09 17:50:08 by grebrune         ###   ########.fr       */
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
	int		test;

	copy = head->env;
	while (copy->next != NULL)
	{
		test = 0;
		big = copy;
		while (copy->next != NULL)
		{
			if (0 <= ft_strcmp(big->name, copy->name))
				if (0 < ft_strcmp(big->next->value, copy->next->value))
					big = copy;
			copy = copy->next;
			test++;
		}
		printf("declare -x %s%s == %d\n", big->name, big->value, test);
		big->next->prev = big->prev;
		big->prev->next = big->next;
		copy = big;
		while (copy->prev != NULL)
			copy = copy->prev;
	}
//	printf("declare -x %s%s\n", copy->name, copy->value);
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
