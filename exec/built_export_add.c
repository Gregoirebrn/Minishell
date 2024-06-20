/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:11:01 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/20 12:31:25 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//to do
//addition in export
// separate search of name in the export main function

int	export_search_env(t_env *c_env, t_head *head)
{
	while (c_env)
	{
		if (0 == ft_strcmp_until(c_env->name, head->cmd->arg[1]))
		{
			c_env->value = replace_var_until(c_env->value, head->cmd->arg[1]);
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