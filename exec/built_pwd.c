/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:48:06 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/08 16:11:24 by grebrune         ###   ########.fr       */
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
		exit_free(head, 2);
	if (str)
		printf("%s\n", str);
	free(str);
	exit_free(head, 0);
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
				return (perror("bash: getcwd"), 2);
		}
		size += 10;
	}
	return (0);
}

char	*value_of_name(t_env *env, char *name)
{
	t_env	*copy;

	copy = env;
	while (copy)
	{
		if (0 == ft_strcmp(copy->name, name))
			return (copy->value);
		copy = copy->next;
	}
	return (NULL);
}
