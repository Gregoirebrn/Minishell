/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:47:13 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/20 18:33:54 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo_newline(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (i == 0 && str[i] == '-')
			i++;
		else if (i != 0 && str[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	echo_pipe(t_head *head, t_cmd *copy)
{
	char	*str;

	if (copy->prev)
	{
		str = get_next_line(0);
		while (str)
		{
			free(str);
			str = get_next_line(0);
		}
	}
	write(1, "\n", 1);
	free_fnp(head, head->fnp);
	ft_free_all(head);
	exit (0);
}

void	ft_echo(t_head *head, t_cmd *copy)
{
	int		i;
	int		n;

	i = 1;
	n = 0;
	if (!copy->arg[1])
		echo_pipe(head, copy);
	while (echo_newline(copy->arg[i]))
	{
		i++;
		n++;
	}
	if (ft_strcmp("$?", copy->arg[i]) == 0)
	{
		printf("%d", g_error);
		if (n == 0)
			printf("\n");
		exit(0);
	}
	print_tab(head, copy->arg, i, n);
}

void	print_tab(t_head *head, char **arg, int i, int n)
{
	while (arg[i])
	{
		ft_putstr(arg[i]);
		i++;
		if (arg[i])
			write(1, " ", 1);
	}
	if (n == 0)
		printf("\n");
	free_fnp(head, head->fnp);
	ft_free_all(head);
	exit(0);
}
