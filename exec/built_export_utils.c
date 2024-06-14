/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:46:00 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/14 15:44:00 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

char	*dup_until(char *str)
{
	size_t	size;
	size_t	i;
	char	*ptr;

	size = 0;
	while (str && str[size] && str[size] != '=')
		size++;
	ptr = malloc((size + 1) * sizeof(char));
	if (ptr == NULL)
		return (ptr);
	i = 0;
	while (i < size)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	*dup_if(char *name, char *value)
{
	size_t	i;

	i = 0;
	while (name && name[i] && name[i] != '=')
		i++;
	if (!(name[i] == '=' && name[i + 1] != '\0'))
	{
		if (!value)
			return (ft_strdup("\0"));
		return (ft_strdup(value));
	}
	return (ft_strdup(&name[i + 1]));
}

int	ft_strcmp_until(char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != 0 || s2[i] != 0)
	{
		if ((s1[i] == 0 || s2[i] == 0) && (s2[i] == '=' || s1[i] == '='))
			return (0);
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

void	free_tab(char **tab)
{
	int	x;

	x = 0;
	while (tab[x])
		free(tab[x++]);
	free(tab);
}
