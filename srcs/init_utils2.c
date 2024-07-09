/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:10:22 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/08 21:58:20 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*env_if_empty(void)
{
	t_env	*new;
	t_env	*env;
	char	*str;

	env = NULL;
	str = NULL;
	if (get_path(&str) == 2)
		return (NULL);
	new = ft_env_new_bis("PWD", str);
	if (new == NULL)
		return (NULL);
	ft_envadd_back(&env, new);
	new = ft_env_new_bis("SHLVL", "1");
	if (new == NULL)
		return (NULL);
	ft_envadd_back(&env, new);
	return (env);
}
