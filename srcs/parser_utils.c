/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:21:52 by beroy             #+#    #+#             */
/*   Updated: 2024/04/22 13:39:14 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ft_cmd_new(char *input)
{
	t_cmd	*s_new;

	s_new = malloc(sizeof(t_cmd));
	if (s_new == NULL)
		return (s_new);
	s_new->line = input;
	s_new->arg = NULL;
	s_new->redir = NULL;
	s_new->next = NULL;
	s_new->prev	= NULL;
	return (s_new);
}

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last = ft_cmdlast(*lst);
			last->next = new;
			last->next->prev = last;
		}
	}
}
