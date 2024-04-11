/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:21:38 by beroy             #+#    #+#             */
/*   Updated: 2023/11/14 13:59:57 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	while (((unsigned char *)s)[i] && i != start)
		i++;
	if (len > ft_strlen((char *)s) - i)
		len = ft_strlen((char *)s) - i;
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (str);
	j = 0;
	while (j < len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = 0;
	return (str);
}
