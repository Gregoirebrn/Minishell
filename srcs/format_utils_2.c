/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:55:23 by beroy             #+#    #+#             */
/*   Updated: 2024/05/14 16:20:21 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int find_var(char* str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		index_up(str, &i);
	}
	return (-1);
}

int str_cmp_var(char *str, int i, char *value)
{
	int j;

	j = 0;
	while (str[i] && value[j] && char_is_ws(str[i]) && str[i] == value[j])
	{
		i++;
		j++;
	}
	if ((str[i] == 0 || char_is_ws(str[i])) && value[j] == 0)
		return (1);
	return (0);
}

char *var_value(char *str, int i, t_env *env)
{
	char	*value;

	value = NULL;
	while (env)
	{
		if (str_cmp_var(str, i, env->value) == 1)
		{
			value = ft_strdup(env->value);
			if (value == NULL)
				return (rewind_env(env), NULL);
		}
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	if (value == NULL && str_cmp_var(str, i, "?"))
		value = ft_strdup("'$?'");
	rewind_env(env);
	return (value);
}

int find_end_var(char *str, int i)
{
	while (str[i])
	{
		if (char_is_ws(str[i]) != 1)
			break ;
		index_up(str, &i);
	}
	return (i);
}

int replace_var(char *str, t_head *head)
{
	int		start;
	int 	end;
	char	*value;

	start = find_var(str);
	end = find_end_var(str, start);
	value = var_value(str, start + 1, head->env);
	if (value == NULL)
		return (1);
	str = str_dup_var(str, start, end + 1, value);
	if (str == NULL)
		return (1);
	return (0);
}