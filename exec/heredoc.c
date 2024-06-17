/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:45:32 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/17 17:48:50 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc(t_head *head)
{
	//checker les redirs
	if (!head->cmd->redir && head->cmd->redir->type != 3)
		return (0);
	//verifier le EOF si il est avec ou sans ""
	//gnl
	//imprimer dans un tmp_file
	//sortir le tt en fd[1]
	//gestion d'erreurs
}