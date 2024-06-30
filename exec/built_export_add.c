/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:11:01 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/28 15:47:07 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_search_env(t_env *c_env, char *name)
{
	while (c_env)
	{
		if (0 == ft_strcmp_until(c_env->name, name))
		{
			c_env->value = replace_var_until(c_env->value, name);
			if (!c_env->value)
				return (write(2, "Crash of Malloc\n", 16), 2);
			return (1);
		}
		c_env = c_env->next;
	}
	return (0);
}

void	error_handle(char *str)
{
	write(2, "bash: export: `", 15);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
}

char	*strcat_until(char *val, char *name)
{
	int		i;
	int		x;
	char	*new_val;

	i = 0;
	while (name && name[i])
		i++;
	i += ft_strlen(val);
	i -= ft_strlen_until(name);
	new_val = malloc(sizeof(char) * (i + 1));
	if (!new_val)
		return (NULL);
	i = -1;
	while (val && val[++i])
		new_val[i] = val[i];
	x = ft_strlen_until(name);
	x++;
	while (name && name[x])
		new_val[i++] = name[x++];
	new_val[i] = 0;
	return (free(val), new_val);
}

int	add_var(t_head *head, char *name, t_env *c_env)
{
	while (c_env)
	{
		if (0 == ft_strcmp_until(c_env->name, name))
		{
			c_env->value = strcat_until(c_env->value, name);
			if (!c_env->value)
				return (write(2, "Crash of Malloc\n", 16), 2);
			return (1);
		}
		c_env = c_env->next;
	}
	if (new_var(head, name))
		return (write(2, "Crash of Malloc\n", 16), 2);
	return (0);
}

void	new_var_bis(t_env *copy, t_head *head, t_env *new)
{
	if (copy)
	{
		copy->next = new;
		new->prev = copy;
	}
	else
	{
		head->env = new;
		new->prev = NULL;
	}
}
