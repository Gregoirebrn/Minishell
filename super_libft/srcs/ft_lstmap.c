/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:14:01 by beroy             #+#    #+#             */
/*   Updated: 2023/11/14 15:06:13 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*head;
	void	*tmp;

	head = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		tmp = f(lst->content);
		new = ft_lstnew(tmp);
		if (new == NULL)
		{
			del(tmp);
			ft_lstclear(&head, del);
			return (head);
		}
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}
