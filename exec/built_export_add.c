/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:11:01 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/19 20:24:35 by grebrune         ###   ########.fr       */
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
	ft_putstr(str);
	write(2, "': not a valid identifier\n", 26);
}

void	add_var(char *str, t_env *c_env)
{
	to do biatch
}