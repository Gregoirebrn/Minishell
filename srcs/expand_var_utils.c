/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:55:23 by beroy             #+#    #+#             */
/*   Updated: 2024/06/19 14:06:05 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (i == 0)
				return (i);
			if (i > 0 && str[i - 1] != '\\')
				return (i);
			if (i > 1 && str[i - 1] == '\\' && str[i - 2] == '\\')
				return (i);
		}
		single_index_up(str, &i);
	}
	return (-1);
}

int	str_cmp_var(char *str, int i, char *value)
{
	int	j;

	j = 0;
	while (str[i] && value[j] && str[i] == value[j])
	{
		i++;
		j++;
	}
	if ((str[i] == 0 || str[i] == '$' || str[i] == 34
			|| char_is_ws(str[i])) && value[j] == 0)
		return (1);
	return (0);
}

char	*var_value(char *str, int i, t_env *env)
{
	char	*value;

	value = NULL;
	while (env && value == NULL)
	{
		if (str_cmp_var(str, i, env->name) == 1)
		{
			value = ft_strdup(env->value);
			if (value == NULL)
				return (NULL);
		}
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	if (value == NULL && str_cmp_var(str, i, "?"))
		value = ft_itoa(g_error);
	if (value == NULL)
		value = ft_strdup("");
	while (env && env->prev)
		env = env->prev;
	return (value);
}

int	find_end_var(char *str, int i)
{
	i++;
	while (str && str[i])
	{
		if (char_is_ws(str[i]) == 1 || str[i] == '$' || str[i] == 34)
			break ;
		if (char_is_num(str[i]) == 1)
			return (i + 1);
		single_index_up(str, &i);
	}
	return (i);
}

int	replace_var_line(char *str, t_head *head)
{
	int		start;
	int		end;
	char	*value;

	start = find_var(str);
	end = find_end_var(str, start);
	value = var_value(str, start + 1, head->env);
	if (value == NULL)
		return (1);
	head->cmd->line = str_dup_var(str, start, end, value);
	if (str == NULL)
		return (1);
	return (0);
}
