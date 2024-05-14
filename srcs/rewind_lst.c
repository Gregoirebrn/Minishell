/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewind_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:17:44 by beroy             #+#    #+#             */
/*   Updated: 2024/05/14 15:24:40 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void rewind_env(t_env *lst)
{
	while (lst->prev)
		lst = lst->prev;
}

void rewind_redir(t_redir *lst)
{
	while (lst->prev)
		lst = lst->prev;
}

void rewind_cmd(t_cmd *lst)
{
	while (lst->prev)
		lst = lst->prev;
}
