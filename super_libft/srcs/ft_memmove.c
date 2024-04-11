/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:57:04 by beroy             #+#    #+#             */
/*   Updated: 2023/11/07 13:57:05 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (dest);
	if (src < dest)
		while (n-- > 0)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
