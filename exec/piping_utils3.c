/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:44:44 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/27 14:09:32 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	dup_of_fd(int fd[2], t_cmd *copy)
{
	if (copy->prev != NULL)
	{
		if (dup2(fd[0], 0) < 0)
			return (perror("dup2"));
		close(fd[0]);
	}
	else
		fd[0] = 0;
	if (copy->next != NULL)
	{
		if (dup2(fd[1], 1) < 0)
			return (perror("dup2"));
		close(fd[1]);
	}
	else
		fd[1] = 1;
}