/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_no_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:09:17 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/28 11:38:35 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	ex_no_args(t_head *head)
{
	char	**tab;
	t_env	*copy;

	if (!head->env)
	{
		free_fnp(head, head->fnp);
		ft_free_all(head);
		exit(0);
	}
	copy = head->env;
	tab = env_to_tab(copy);
	if (!tab)
	{
		write(2, "Crash of Malloc\n", 16);
		ft_exit(head);
	}
	swap_this_tab(tab);
	printf_tab(tab);
	free_tab(tab);
	close_pipe(head, head->fnp->pipe);
	free_fnp(head, head->fnp);
	ft_free_all(head);
	exit(0);
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
			return (free_tab(tab), NULL);
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

void	swap_this_tab(char **tab)
{
	int		x;
	char	*tmp;

	x = 0;
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
