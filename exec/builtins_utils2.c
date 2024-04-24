/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:04:21 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/24 17:25:01 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	change_old_pwd(t_head *head, char *old_pwd)
{
	t_env	*copy;

	copy = head->env;
	while (copy->next != NULL)
	{
		if (ft_strncmp(copy->name, "OLDPWD", 7))
		{
			free(copy->value);
			copy->value = old_pwd;
		}
		copy = copy->next;
	}
}

void	replace_var(char **arg, char *result)
{
	int		z;

	free(*(arg));
	*arg = calloc((strlen(result) + 1), sizeof (char));
	z = 0;
	while (result[z])
	{
		*(arg[z]) = result[z];
		z++;
	}
	*(arg[z]) = '\0';
}

void	ft_free_tab(char **tab, size_t i)
{
	while (i > 0)
	{
		free(tab[i])
		i--;
	}
	free(tab);
}

void	print_in_order(char **tab)
{
	size_t	number;
	size_t	i;

	i = 0;
	while (tab[i])
	{
		if (0 < ft_strcmp(tab[i], tab[i + 1]))
			number = i;
		i++;
		if (i == size)
		{
			i = 0;
			printf("declare -x %s", tab[num]);
		}
	}
}

int	ex_no_args(t_head *head)
{
	t_env	*copy;
	char	**tab;
	size_t	size;
	size_t	i;

	copy = head->env;
	size = len_struct(copy);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (1);
	i = 0;
	while (i < size)
	{
		tab[i] = join_with_char(head->env->name, head->env->value, '=');
		if (!tab[i])
			return (ft_free_tab(tab, i));
		i++;
	}
	print_in_order(tab);
	ft_free_tab(tab, i);
	//find first line in alpha sorting
	//display it with declare -x
	//remove from the list the line and recall
}
