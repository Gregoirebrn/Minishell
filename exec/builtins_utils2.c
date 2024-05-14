/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:04:21 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/14 16:12:15 by grebrune         ###   ########.fr       */
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

int		add_env(t_head *head, char *name, char *value)
{
	t_env	*new;
	t_env	*copy;

	copy = head->env;
	new = malloc(sizeof(t_env));
	if (!new)
		return (2);
	while (copy->next)
		copy = copy->next;
	copy->next = new;
	new->prev = copy;
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = "\0";
	return (0);
}

void	print_tab(char **arg, int i, int n, int fd)
{
	while (arg[i])
	{
		ft_putstr_fd(arg[i], fd);
		i++;
	}
	if (n == 0)
		printf("\n");
}