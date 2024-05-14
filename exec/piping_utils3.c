/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:44:44 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/14 15:54:57 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	dup_of_fd(int fd[2], t_cmd *copy)
{
	if (copy->prev != NULL)
		if (0 > dup2(fd[0], 0))
			return (perror("dup2"));
	if (copy->next != NULL)
		if (0 > dup2(fd[1], 1))
			return (perror("dup2"));
}