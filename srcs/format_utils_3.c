/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:10:02 by beroy             #+#    #+#             */
/*   Updated: 2024/05/14 16:10:06 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*str_dup_var(char *str, int start, int end, char *value)
{
	int i;
	int j;
	char *dup;

	i = 0;
	j = 0;
	dup = ft_calloc(ft_strlen(str) - end + start + ft_strlen(value), sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (i < start)
	{
		dup[j] = str[i];
		i++;
		j++;
	}
	i = 0;
	while (value[i])
	{
		dup[j] = value[i];
		i++;
		j++;
	}
	while (str[end])
	{
		dup[j] = str[end];
		end++;
		j++;
	}
	return (free(str), dup);
}