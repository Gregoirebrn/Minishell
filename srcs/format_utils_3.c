/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:10:02 by beroy             #+#    #+#             */
/*   Updated: 2024/05/21 18:13:48 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*str_dup_var(char *str, int start, int end, char *value)
{
	int i;
	int j;
	char *dup;

	i = 0;
	j = 0;
	printf("str: %s | start: %d | end: %d | value: %s\n", str, start, end, value);
	dup = ft_calloc(ft_strlen(str) - end + start + ft_strlen(value) + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (i < start)
	{
		dup[j] = str[i];
		i++;
		j++;
	}
	i = 0;
	while (value[i])
	{
		dup[j] = value[i];
		i++;
		j++;
	}
	while (str[end])
	{
		dup[j] = str[end];
		end++;
		j++;
	}
	return (free(str), free(value), dup);
}

int replace_var_redir(char *str, t_head *head)
{
	int		start;
	int 	end;
	char	*value;

	start = find_var(str);
	end = find_end_var(str, start);
	value = var_value(str, start + 1, head->env);
	if (value == NULL)
		return (1);
	head->cmd->redir->arg = str_dup_var(str, start, end, value);
	if (str == NULL)
		return (1);
	return (0);
}
