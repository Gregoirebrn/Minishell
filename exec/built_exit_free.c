/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:13:12 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/28 17:21:12 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_free(t_head*head, int status)
{
	free_fnp(head, head->fnp);
	ft_free_all(head);
	exit (status);
}

void	new_pwd(t_head *head, char *value, char *name)
{
	t_env	*new;
	t_env	*copy;

	copy = head->env;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return ;
	while (copy && copy->next)
		copy = copy->next;
	new_var_bis(copy, head, new);
	new->next = NULL;
	new->name = ft_strdup(name);
	if (!new->name)
		return ;
	new->value = ft_strdup(value);
	if (!new->value)
		return ;
	return ;
}
