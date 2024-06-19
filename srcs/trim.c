/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:00:48 by beroy             #+#    #+#             */
/*   Updated: 2024/06/19 14:06:05 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nbr_quote(char *str)
{
	int		i;
	int		nbr;
	char	find;

	i = 0;
	nbr = 0;
	while (str && str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			find = str[i];
			if (quote_skip(str, &i, find) == 1)
				nbr++;
			else
				nbr += 2;
		}
		i++;
	}
	return (nbr);
}

void	trim_str_2(char *str, char *trim, int len, int nbr)
{
	int		i;
	int		j;
	int		trigger;
	char	find;

	i = 0;
	j = 0;
	trigger = 0;
	while (i < len - nbr)
	{
		if (trigger == 0 && (str[j] == 34 || str[j] == 39))
		{
			find = str[j];
			trigger = 1;
			j++;
		}
		if (trigger == 1 && str[j++] == find)
		{
			trigger = 0;
			j++;
		}
		trim[i++] = str[j++];
	}
}

char	*trim_str(char *str)
{
	char	*trim;
	int		len;
	int		nbr;

	nbr = nbr_quote(str);
	if (nbr <= 1)
		return (str);
	len = (int)strlen(str);
	trim = calloc(len - nbr + 1, sizeof(char));
	if (trim == NULL)
		return (NULL);
	trim_str_2(str, trim, len, nbr);
	free(str);
	return (trim);
}

int	trim_tab(char **tab)
{
	int	i;

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

int	format(t_head *head)
{
	while (head->cmd)
	{
		if (trim_tab(head->cmd->arg) == 1)
			return (1);
		if (head->cmd->next == NULL)
			break ;
		head->cmd = head->cmd->next;
	}
	while (head->cmd->prev)
		head->cmd = head->cmd->prev;
	return (0);
}
