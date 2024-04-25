/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:00:48 by beroy             #+#    #+#             */
/*   Updated: 2024/04/25 16:10:49 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *trim_str(char *str)
{
	int		i;
	char	*trim;
	int 	len;

	i = 0;
	printf("str : %s\n", str);
	if (str[i] != 34 && str[i] != 39)
		return (str);
	len = ft_strlen(str);
	printf("len: %d\n", len);
	trim = calloc(len - 2 + 1, sizeof(char));
	if (trim == NULL)
		return (NULL);
	while (i < len - 2)
	{
		trim[i] = str[i + 1];
		i++;
	}
	free(str);
	printf("trim : %s\n", trim);
	return (trim);
}

int trim_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		tab[i] = trim_str(tab[i]);
		if (tab[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}

int format(t_head *head)
{
	while (head->cmd)
	{
		if (trim_tab(head->cmd->arg) == 1)
			return (1);
		if (head->cmd->next == NULL)
			break ;
		head->cmd = head->cmd->next;
	}
	return (0);
}
