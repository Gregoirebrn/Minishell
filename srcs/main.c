/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:11:53 by beroy             #+#    #+#             */
/*   Updated: 2024/04/25 16:13:26 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_cmd(t_cmd *cmd)
{
	t_redir	*tmp;

	if (cmd->arg != NULL)
		ft_splitdestroy(cmd->arg);
	while (cmd->redir != NULL)
	{
		free(cmd->line);
		tmp = cmd->redir->next;
		free(cmd->redir->arg);
		free(cmd->redir);
		cmd->redir = tmp;
	}
	if (cmd != NULL)
		free(cmd);
}

void	ft_free_all(t_head *head)
{
	t_env	*tmp;

	if (head->cmd != NULL)
		ft_free_cmd(head->cmd);
	while (head->env != NULL)
	{
		tmp = head->env->next;
		free(head->env->name);
		free(head->env->value);
		free(head->env);
		head->env = tmp;
	}
	if (head != NULL)
		free(head);
}

char	*ft_color(int i)
{
	if (i % 6 == 0)
		return (YELLOW);
	if (i % 6 == 1)
		return (GREEN);
	if (i % 6 == 2)
		return (CYAN);
	if (i % 6 == 3)
		return (BLUE);
	if (i % 6 == 4)
		return (PURPLE);
	else
		return (RED);
}

void	ft_header(void)
{
	char	*str;
	char	*color;
	int 	fd;
	int 	i;

	fd = open("data/header.txt", O_RDONLY);
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		color = ft_color(i);
		printf("%s%s", color, str);
		str = get_next_line(fd);
		i++;
	}
	printf("\033[0m\n");
}

int	main(void)
{
	char	*input;
	t_head	*head;

	ft_header();
	head = head_init();
	if (head == NULL)
		return (0);
	while (42)
	{
		input = readline("> ");
		add_history(input);
		if (ft_parse(input, head) == 0)
		{
			if (format(head) == 1)
			{
				ft_free_cmd(head->cmd);
				break ;
			}
			while (head->cmd)
			{
				printf("line: %s\n", head->cmd->line);
				tab_display(head->cmd->arg);
				if (head->cmd->next == NULL)
					break ;
				head->cmd = head->cmd->next;
			}
			while (head->cmd->prev)
				head->cmd = head->cmd->prev;
			ft_free_cmd(head->cmd);
		}
	}
	return (ft_free_all(head), 0);
}
