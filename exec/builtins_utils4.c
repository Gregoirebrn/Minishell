/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:35:19 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/12 19:03:59 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_name(char *name)
{
	int	i;

	i = 0;
	while (name && name[i])
	{
		if (ft_isalpha(name[i]) == 0)
		{
			if (ft_isdigit(name[i]) == 0)
				return (1);
		}
		i++;
	}
	printf("fuck");
	return (0);
}
