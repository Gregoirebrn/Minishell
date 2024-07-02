/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:44:43 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/02 20:12:08 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_error_exit(char **arg, char *str, char **env, char **path)
{
	perror(arg[0]);
	free_tab(env);
	free_tab(path);
	free_tab(arg);
	ft_free(str);
	if (errno == EACCES)
		exit (126);
	else
		exit (127);
}