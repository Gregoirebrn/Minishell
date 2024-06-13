/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:35:19 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/13 14:50:43 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_name(char *name)
{
	int	i;

	i = 0;
	if (ft_strcmp("", name) == 0)
		return (ft_printf_fd(2, "bash: export: `': not a "\
								"valid identifier\n"), 1);
	if (ft_strcmp("=", name) == 0)
		return (g_error = 1, ft_printf_fd(2, "bash: export: `%s': not a "\
								"valid identifier\n", name), 1);
	while (name && name[i] && name[i] != '=')
	{
		if (ft_isalpha(name[i]) == 0)
		{
			if (ft_isdigit(name[i]) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_strlen_until(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*replace_var_until(char *arg, char *result)
{
	int		z;
	int		i;
	char	*ret;

	free(arg);
	z = ft_strlen_until(result);
	i = 0;
	while (result && result[z + 1 + i])
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (result && result[z + 1 + i])
	{
		ret[i] = result[z + 1 + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}
