/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:21:42 by beroy             #+#    #+#             */
/*   Updated: 2023/11/09 12:29:56 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	if ((unsigned char)c == 0)
		return ((char *)s + ft_strlen((char *)s));
	i = ft_strlen((char *)s);
	if (i == 0)
		return (NULL);
	i -= 1;
	while (s[i] != (unsigned char)c && i)
		i--;
	if (i == 0 && s[0] != (unsigned char)c)
		return (NULL);
	return ((char *)s + i);
}
