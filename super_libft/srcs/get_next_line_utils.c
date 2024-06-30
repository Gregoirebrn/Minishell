/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:01:53 by beroy             #+#    #+#             */
/*   Updated: 2024/01/17 16:17:27 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup_nl(char *str)
{
	size_t	i;
	size_t	len;
	char	*dup;

	len = 0;
	while (str[len] != '\n' && str[len] != 0)
		len++;
	if (str[len] == '\n')
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (dup);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

int	ft_linecheck(char *str)
{
	size_t	i;

	i = 0;
	if (ft_strlen(str + i) == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_nl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*join;

	len = 0;
	while (s2[len] != '\n' && s2[len] != 0)
		len++;
	if (s2[len] == '\n')
		len++;
	join = malloc(sizeof(char) * (ft_strlen(s1) + len + 1));
	if (join == NULL)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2 && j++ < len)
		join[i + j - 1] = s2[j - 1];
	join[i + j - 1] = 0;
	free (s1);
	return (join);
}

void	ft_buffclean(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] != '\n' && str[i] != 0)
		i++;
	if (str[i] == '\n')
		i++;
	j = 0;
	while (str[i + j])
	{
		str[j] = str[i + j];
		j++;
	}
	str[j] = 0;
}
