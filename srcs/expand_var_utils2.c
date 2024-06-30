/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:32:58 by beroy             #+#    #+#             */
/*   Updated: 2024/06/28 18:37:44 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	end_of_var(char c)
{
	if (char_is_num(c) == 1)
		return (0);
	if (c == '_')
		return (0);
	if (c >= 65 && c <= 90)
		return (0);
	if (c >= 97 && c <= 122)
		return (0);
	return (1);
}
