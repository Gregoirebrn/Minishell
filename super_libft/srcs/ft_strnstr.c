/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:56:43 by beroy             #+#    #+#             */
/*   Updated: 2023/11/09 14:57:18 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	lilen;

	if (!little[0])
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	lilen = ft_strlen((char *)little);
	while (big[i] && i < len)
	{
		if (i + lilen > len)
			return (NULL);
		if (ft_strncmp((char *)big + i, little, lilen) == 0)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
