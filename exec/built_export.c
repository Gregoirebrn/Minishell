/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:51:12 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/14 16:11:12 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_export(t_head *head)
{
	t_env	*c_env;

	c_env = head->env;
	if (head->cmd->arg[1] == NULL)
		ex_no_args(head);
	if (head->cmd->next != NULL)
		return (3);
	if (check_name(head->cmd->arg[1]))
		return (1);
	while (c_env)
	{
		if (0 == ft_strcmp_until(c_env->name, head->cmd->arg[1]))
		{
			c_env->value = replace_var_until(c_env->value, head->cmd->arg[1]);
			if (!c_env->value)
				return (ft_printf_fd(2, "Crash of Malloc\n"), 2);
			return (0);
		}
		c_env = c_env->next;
	}
	if (2 == add_env(head, head->cmd->arg[1], head->cmd->arg[2]))
		return (ft_exit(head), 2);
	return (0);
}

void	ex_no_args(t_head *head)
{
	char	**tab;
	t_env	*copy;

	copy = head->env;
	tab = env_to_tab(copy);
	if (!tab)
	{
		printf("Crash of Malloc\n");
		ft_exit(head);
	}
	swap_this_tab(tab);
	printf_tab(tab);
	free_tab(tab);
	ft_exit(head);
}

int	check_name(char *name)
{
	int	i;

	i = 0;
	if (ft_strcmp("", name) == 0)
		return (ft_printf_fd(2, "bash: export: `': not a "\
								"valid identifier\n"), 1);
	if (ft_strcmp("=", name) == 0)
		return (g_error = 1, ft_printf_fd(2, "bash: export: `%s': not a "\
								"valid identifier\n", name), 1);
	while (name && name[i] && name[i] != '=')
	{
		if (ft_isalpha(name[i]) == 0)
		{
			if (ft_isdigit(name[i]) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	add_env(t_head *head, char *name, char *value)
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
	new->name = dup_until(name);
	if (!new->name)
		return (2);
	new->value = dup_if(name, value);
	if (!new->value)
		return (2);
	new->next = NULL;
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
