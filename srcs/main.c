/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:11:53 by beroy             #+#    #+#             */
/*   Updated: 2024/07/08 21:44:00 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error = 0;

int	single_exec(t_head *head, char *input)
{
	sig_main(head, 0);
	if (input == NULL || str_empty(input) == 1)
		return (0);
	if (ft_parse(input, head) == 0)
	{
		heredoc(head);
		if (cmd_is_empty(head->cmd, 0) == 0)
			executable(head);
	}
	return (0);
}

int	open_on_err(t_cmd *cmd)
{
	t_cmd	*c_cmd;
	t_redir	*c_red;

	c_cmd = cmd;
	while (c_cmd)
	{
		c_red = c_cmd->redir;
		while (c_red)
		{
			if (c_red->type == 1)
				c_red->fd = open(c_red->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (c_red->type == 2)
				c_red->fd = open(c_red->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if ((c_red->type == 2 || c_red->type == 1) && c_red->fd == -1)
				return (perror(c_red->arg), 2);
			c_red = c_red->next;
		}
		c_cmd = c_cmd->next;
	}
	return (0);
}

void	here_exec(t_head *head, char *input)
{
	if (ft_parse(input, head) == 0)
	{
		if (heredoc(head))
		{
			if (cmd_is_empty(head->cmd, 0) == 0)
				executable(head);
			else
			{
				open_on_err(head->cmd);
				close_pipe();
			}
		}
	}
	if (head->cmd != NULL)
		ft_free_cmd(&(head->cmd));
	free(input);
}

void	main_loop(t_head *head)
{
	char	*input;

	while (42)
	{
		sig_main(head, 0);
		input = readline("> ");
		if (input == NULL)
		{
			free(input);
			break ;
		}
		add_history(input);
		sig_main(head, 3);
		if (str_empty(input) == 1)
		{
			free(input);
			continue ;
		}
		here_exec(head, input);
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
	if (ac == 1)
		main_loop(head);
	if (ac == 2)
		single_exec(head, av[1]);
	return (ft_free_all(head), g_error);
}
