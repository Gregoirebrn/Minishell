/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:14:37 by beroy             #+#    #+#             */
/*   Updated: 2024/06/26 19:38:31 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_env_new(char *env)
{
	t_env	*s_new;
	int		equal;

	equal = find_equal(env) + 1;
	s_new = ft_calloc(1, sizeof(t_env));
	if (s_new == NULL)
		return (s_new);
	s_new->name = ft_substr(env, 0, equal - 1);
	if (s_new->name == NULL)
		return (free(s_new), NULL);
	s_new->value = ft_substr(env, equal, ft_strlen(env) - equal);
	if (s_new->value == NULL)
		return (ft_free(s_new->name), ft_free(s_new), NULL);
	s_new->next = NULL;
	s_new->prev = NULL;
	return (s_new);
}

t_env	*ft_envlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last = ft_envlast(*lst);
			last->next = new;
			new->prev = last;
		}
	}
}

t_env	*env_init(char **env_tab)
{
	int		i;
	t_env	*new;
	t_env	*env;

	if (env_tab && !env_tab[0])
		return (env_if_empty());
	i = 0;
	env = NULL;
	while (env_tab[i])
	{
		new = ft_env_new(env_tab[i]);
		if (new == NULL)
			return (NULL);
		ft_envadd_back(&env, new);
		i++;
	}
	return (env);
}

t_head	*head_init(char **env)
{
	t_head	*head;

	head = ft_calloc(1, sizeof(t_head));
	if (head == NULL)
		return (printf("Malloc failed!\n"), NULL);
	head->env = env_init(env);
	if (head->env == NULL)
		return (printf("Malloc failed!\n"), free(head), NULL);
	head->cmd = NULL;
	return (head);
}
