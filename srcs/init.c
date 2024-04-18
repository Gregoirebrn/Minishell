/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:14:37 by beroy             #+#    #+#             */
/*   Updated: 2024/04/18 17:22:25 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_head	*head_init(void)
{
	t_head	*head;

	head = calloc(1, sizeof(t_head));
	if (head == NULL)
		return (printf("Malloc failed!\n"), NULL);
	head->env = NULL;
	head->cmd = NULL;
	return (head);
}
