/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:46:00 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/20 12:29:16 by grebrune         ###   ########.fr       */
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
	while (str && str[size] && str[size] != '=' && str[size] != '+')
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

char	*dup_if(char *name)
{
	size_t	i;

	i = 0;
	while (name && name[i] && name[i] != '=')
		i++;
	if (!(name[i] == '=' && name[i + 1] != '\0'))
		return (ft_strdup("\0"));
	return (ft_strdup(&name[i + 1]));
}

int	ft_strlen_until(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	int	x;

	x = 0;
	while (tab[x])
		ft_free(tab[x++]);
	ft_free(tab);
}
