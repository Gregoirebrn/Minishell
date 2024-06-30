/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:21:52 by beroy             #+#    #+#             */
/*   Updated: 2024/06/28 15:59:26 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_is_empty(t_redir *redir)
{
	int	ret;

	ret = 1;
	if (!redir)
		return (ret);
	while (redir)
	{
		if (str_empty(redir->arg) == 0)
			ret = 0;
		if (redir->next == NULL)
			break ;
		redir = redir->next;
	}
	while (redir->prev)
		redir = redir->prev;
	return (ret);
}

t_cmd	*ft_cmd_new(char *input)
{
	t_cmd	*s_new;

	s_new = ft_calloc(1, sizeof(t_cmd));
	if (s_new == NULL)
		return (s_new);
	s_new->line = input;
	s_new->arg = NULL;
	s_new->redir = NULL;
	s_new->next = NULL;
	s_new->prev = NULL;
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
			new->prev = last;
		}
	}
}

void	find_pipe(char *input, int *i)
{
	while (input[*i])
	{
		if (input[*i] == '|' || input [*i] == 0)
			return ;
		index_up(input, i);
	}
}
