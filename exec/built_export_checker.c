/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:32:41 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/21 16:48:17 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_name_errors(char *name)
{
	if (ft_strcmp("", name) == 0)
		return (write(2, "bash: export: `': not a valid identifier\n", 41), 1);
	if (ft_strcmp("=", name) == 0)
		return (g_error = 1, write(2, "bash: export: "
				"`=': not a valid identifier\n", 42), 1);
	if (ft_strcmp("+=", name) == 0)
		return (g_error = 1, write(2, "bash: export: "
				"`+=': not a valid identifier\n", 43), 1);
	if (ft_isdigit(name[0]))
		return (error_handle(name), 1);
	return (0);
}

int	check_name(t_head *head, char *name, t_env *c_env)
{
	int	i;

	i = 0;
	if (check_name_errors(name))
		return (1);
	while (name[i] && name[i] != '=')
	{
		if (name[i] == '+' && name[i + 1] == '=')
			return (add_var(head, name, c_env), 0);
		if (ft_isalnum(name[i]) == 0)
			return (error_handle(name), 1);
		i++;
	}
	return (0);
}

int	no_plus(char *name)
{
	size_t	i;

	i = 0;
	while (name && name[i] && name[i] != '=')
	{
		if (name[i] == '+')
			return (0);
		i++;
	}
	return (1);
}
