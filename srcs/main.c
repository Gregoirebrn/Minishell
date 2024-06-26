/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:11:53 by beroy             #+#    #+#             */
/*   Updated: 2024/06/26 20:12:22 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error = 0;

int	single_exec(t_head *head, char *input)
{
	if (input == NULL || str_empty(input) == 1)
		return (0);
	if (ft_parse(input, head) == 0)
	{
		heredoc(head);
		executable(head);
		clear_heredoc(head);
	}
	return (0);
}

void	main_loop(t_head *head)
{
	char	*input;

	while (42)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		add_history(input);
		if (str_empty(input) == 1)
			continue ;
		if (ft_parse(input, head) == 0)
		{
			if (heredoc(head))
				executable(head);
			clear_heredoc(head);
		}
		if (head->cmd != NULL)
			ft_free_cmd(&(head->cmd));
		sig_main(head, 0);
	}
	write(1, "exit\n", 5);
}

int	main(int ac, char **av, char **env)
{
	t_head	*head;

	(void)ac;
	(void)av;
	ft_header();
	head = head_init(env);
	if (head == NULL)
		return (0);
	sig_main(head, 0);
	if (ac == 1)
		main_loop(head);
	if (ac == 2)
		single_exec(head, av[1]);
	return (ft_free_all(head), 0);
}
