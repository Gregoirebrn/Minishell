/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:44:43 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/02 20:24:11 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_error_exit(char **arg, char **env, char **path)
{
	write(2, "bash: ", 6);
	perror(arg[0]);
	if (env)
		free_tab(env);
	if (path)
		free_tab(path);
	free_tab(arg);
	if (errno == EACCES)
		exit (126);
	else
		exit (127);
}
