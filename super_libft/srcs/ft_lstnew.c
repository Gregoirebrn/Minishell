/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:28:15 by sweek             #+#    #+#             */
/*   Updated: 2023/11/13 10:55:18 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*s_new;

	s_new = malloc(sizeof(t_list));
	if (s_new == NULL)
		return (s_new);
	s_new->content = content;
	s_new->next = NULL;
	return (s_new);
}
