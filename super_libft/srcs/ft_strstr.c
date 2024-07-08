/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:00:15 by grebrune          #+#    #+#             */
/*   Updated: 2023/09/20 20:43:40 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	x;

	i = 0;
	while (str[i] != '\0')
	{
		x = 0;
		while (str[i + x] == to_find[x] && to_find[x] != '\0')
		{
			x++;
		}
		if (to_find[x] == '\0')
			return (str + i);
		i++;
	}
	if (str[0] == '\0' && to_find[0] == '\0')
		return (str);
	return (0);
}
