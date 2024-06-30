/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:50:37 by beroy             #+#    #+#             */
/*   Updated: 2023/11/09 16:42:46 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_ischarset(char c, char const *set)
{
	size_t	i;
	size_t	chk;

	i = 0;
	chk = 0;
	while (set[i])
	{
		if (set[i] == c)
			chk++;
		i++;
	}
	if (chk == 0)
		return (0);
	return (1);
}

static char	*ft_strldup(char *s1, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc (sizeof(char) * (len + 1));
	if (str == NULL)
		return (str);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	istart;
	size_t	iend;
	char	*str;

	istart = 0;
	iend = ft_strlen((char *)s1);
	while (s1[istart])
	{
		if (ft_ischarset(s1[istart], set) == 0)
			break ;
		istart++;
	}
	while (iend > istart)
	{
		if (ft_ischarset(s1[iend - 1], set) == 0)
			break ;
		iend--;
	}
	str = ft_strldup((char *)s1 + istart, iend - istart);
	return (str);
}
