/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:48:06 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/21 14:25:54 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_head *head)
{
	int		err;
	char	*str;

	str = NULL;
	err = get_path(&str);
	if (err == 2)
	{
		write(2, "bash: pwd: ", 10);
		perror(str);
	}
	printf("%s\n", str);
	free(str);
	free_fnp(head, head->fnp);
	ft_free_all(head);
	exit(0);
}

int	get_path(char **str)
{
	size_t	size;

	size = 10;
	while (!*(str))
	{
		*str = getcwd(*(str), size);
		if (!*(str))
		{
			free(*(str));
			*(str) = NULL;
			if (errno != ERANGE)
				return (2);
		}
		size += 10;
	}
	return (0);
}

char	*value_of_name(t_env *env, char *name)
{
	t_env	*copy;

	copy = env;
	while (env)
	{
		if (0 == ft_strcmp(env->name, name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
