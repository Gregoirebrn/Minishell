/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:14:37 by beroy             #+#    #+#             */
/*   Updated: 2024/05/14 13:50:52 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_env_new(char *env)
{
	t_env	*s_new;
	int 	equal;

	equal = find_equal(env);
	s_new = malloc(sizeof(t_env));
	if (s_new == NULL)
		return (s_new);
	s_new->name = ft_substr(env, 0, equal);
	if (s_new->name == NULL)
		return (free(s_new), NULL);
	s_new->value = ft_substr(env, equal + 1, ft_strlen(env) - equal);
	if (s_new->value == NULL)
		return (free(s_new->name), free(s_new), NULL);
	s_new->next = NULL;
	s_new->prev	= NULL;
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
	int 	i;
	t_env	*new;
	t_env	*env;

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

	head = calloc(1, sizeof(t_head));
	if (head == NULL)
		return (printf("Malloc failed!\n"), NULL);
	head->env = env_init(env);
	if (head->env == NULL)
		return (printf("Malloc failed!\n"), free(head), NULL);
	head->cmd = NULL;
	return (head);
}
