/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:59:12 by beroy             #+#    #+#             */
/*   Updated: 2024/05/14 15:00:25 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

t_redir	*ft_redir_new(char *line, int start, int end, int type)
{
	t_redir	*s_new;

	s_new = malloc(sizeof(t_redir));
	if (s_new == NULL)
		return (s_new);
	s_new->type = type;
	s_new->arg = ft_substr(line, start, end - start + 1);
	if (s_new->arg == NULL)
		return (free(s_new), NULL);
	s_new->next = NULL;
	s_new->prev = NULL;
	s_new->fd = -1;
	return (s_new);
}

t_redir	*ft_redirlast(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_rediradd_back(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last = ft_redirlast(*lst);
			last->next = new;
			new->prev = last;
		}
	}
}
