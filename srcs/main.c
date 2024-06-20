/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:11:53 by beroy             #+#    #+#             */
/*   Updated: 2024/06/20 18:12:50 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error = 0;

int	single_exec(t_head *head, char *input)
{
	if (input == NULL || str_is_empty(input) == 1)
		return (0);
	if (ft_parse(input, head) == 0)
	{
		heredoc(head);
		executable(head);
		clear_heredoc(head);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_head	*head;

	ft_header();
	head = head_init(env);
	if (head == NULL)
		return (0);
	while (ac == 1)
	{
		input = readline("> ");
		if (input == NULL || str_is_empty(input) == 1)
			continue ;
		add_history(input);
		if (ft_parse(input, head) == 0)
		{
			heredoc(head);
			executable(head);
			clear_heredoc(head);
			ft_free_cmd(head->cmd);
		}
	}
	if (ac == 2)
		single_exec(head, av[1]);
	return (ft_free_all(head), 0);
}
