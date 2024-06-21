/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:51:12 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/21 16:47:33 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_export(t_head *head)
{
	t_env	*c_env;
	size_t	i;

	c_env = head->env;
	if (head->cmd->arg[1] == NULL)
		return (ex_no_args(head));
	if (head->cmd->next != NULL)
		return (3);
	i = 1;
	while (head->cmd->arg[i])
	{
		if (export_bis(head, c_env, i))
			return (2);
		i++;
	}
	return (0);
}

int	export_bis(t_head *head, t_env *c_env, size_t i)
{
	if (check_name(head, head->cmd->arg[i], c_env))
		return (1);
	if (no_plus(head->cmd->arg[i]))
	{
		if (export_search_env(c_env, head->cmd->arg[i]) == 0)
		{
			if (2 == new_var(head, head->cmd->arg[i]))
				return (write(2, "Crash of Malloc\n", 16), 2);
		}
		else
			return (1);
	}
	return (0);
}

int	ft_strcmp_until(char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != 0 || s2[i] != 0)
	{
		if (s1[i] == 0 && s2[i] == '+')
			return (0);
		if (s2[i] == '=' || s1[i] == '=')
			return (0);
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

char	*replace_var_until(char *arg, char *result)
{
	int		z;
	int		i;
	char	*ret;

	free(arg);
	z = ft_strlen_until(result);
	i = 0;
	while (result && result[z + 1 + i])
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (result && result[z + 1 + i])
	{
		ret[i] = result[z + 1 + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	new_var(t_head *head, char *name)
{
	t_env	*new;
	t_env	*copy;

	copy = head->env;
	if (check_equal(name))
		return (g_error = 0, 0);
	new = malloc(sizeof(t_env));
	if (!new)
		return (2);
	while (copy->next)
		copy = copy->next;
	copy->next = new;
	new->prev = copy;
	new->next = NULL;
	new->name = dup_until(name);
	if (!new->name)
		return (2);
	new->value = dup_if(name);
	if (!new->value)
		return (2);
	return (0);
}
