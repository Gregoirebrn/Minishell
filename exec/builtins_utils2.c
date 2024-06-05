/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:04:21 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/05 13:22:53 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	replace_value(t_head *head, char *value, char *replace)
{
	t_env	*copy;

	copy = head->env;
	while (copy->next != NULL)
	{
		if (ft_strcmp(copy->name, replace) == 0)
		{
			free(copy->value);
			copy->value = value;
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

void	print_tab(char **arg, int i, int n, int fd[2])
{
	while (arg[i])
	{
		ft_putstr_fd(arg[i], fd[1]);
		i++;
	}
	if (n == 0)
		printf("\n");
}

void	cd_no_arg(t_head *head, char **str)
{
	t_env	*env;

	env = head->env;
	while (env)
	{
		if (ft_strcmp(env->name, "HOME") == 0)
		{
			*str = env->value;
			break ;
		}
		env = env->next;
	}
}