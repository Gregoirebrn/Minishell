/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:09:17 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/05 15:11:32 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	free_tab(char **tab, int x)
{
	while (--x >= 0)
		free(tab[x]);
	free(tab);
}

char	*join_equal(char *name, char *val)
{
	char	*n_w_e;
	char	*v_w_e;
	char	*join;

	n_w_e = ft_strjoin(name, "=\"");
	v_w_e = ft_strjoin(val, "\"");
	join = ft_strjoin(n_w_e, v_w_e);
	free(n_w_e);
	free(v_w_e);
	return (join);
}

char	**env_to_tab(t_env *copy)
{
	char	**tab;
	size_t	x;

	tab = malloc((sizeof (char *)) * (envlen(copy) + 2));
	if (!tab)
		return (NULL);
	x = 0;
	while (copy)
	{
		tab[x] = join_equal(copy->name, copy->value);
		if (!tab[x])
			return (free_tab(tab, x), NULL);
		x++;
		copy = copy->next;
	}
	tab[x] = NULL;
	return (tab);
}

void	printf_tab(char **tab)
{
	size_t	x;

	x = 0;
	while (tab[x] != NULL)
	{
		if (ft_strncmp("_=\"/home", tab[x], 8) != 0)
			printf("declare -x %s\n", tab[x]);
		x++;
	}
}

void	ex_no_args(t_head *head)
{
	char	**tab;
	t_env	*copy;
	size_t	x;
	char	*tmp;

	copy = head->env;
	x = 0;
	tab = env_to_tab(copy);
	if (!tab)
	{
		printf("Crash of Malloc\n");
		ft_exit(head);
	}
	while (tab[x] && tab[x + 1])
	{
		if (0 < ft_strcmp(tab[x], tab[x + 1]))
		{
			tmp = tab[x];
			tab[x] = tab[x + 1];
			tab[x + 1] = tmp;
			x = 0;
		}
		else
			x++;
	}
	printf_tab(tab);
	free_tab(tab, x);
	ft_exit(head);
}
