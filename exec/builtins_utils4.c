/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:35:19 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/12 20:07:33 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_name(char *name)
{
	int	i;

	i = 0;
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

void	replace_var_until(char **arg, char *result)
{
	int		z;
	int		i;

	free(*(arg));
	z = ft_strlen_until(result);
	i = 0;
	while (result && result[z + i])
		i++;
	*arg = calloc((i + 1), sizeof (char));
	i = 0;
	while (result[z + i])
	{
		*(arg[i]) = result[z + i];
		i++;
	}
	*(arg[i]) = '\0';
}
