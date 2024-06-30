/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:30:06 by beroy             #+#    #+#             */
/*   Updated: 2023/11/07 14:30:06 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	isrc;
	unsigned int	idest;
	unsigned int	destlen;
	unsigned int	srclen;

	isrc = 0;
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	idest = destlen;
	if (size == 0)
		return (srclen);
	while (src[isrc] && idest < size - 1)
	{
		dest[idest] = src[isrc];
		idest++;
		isrc++;
	}
	dest[idest] = 0;
	if (size < idest)
		return (srclen + size);
	return (destlen + srclen);
}
