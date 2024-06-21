/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:11:53 by beroy             #+#    #+#             */
/*   Updated: 2024/06/20 18:26:42 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error = 0;

void	ft_free_cmd(t_cmd *cmd)
{
	t_redir	*tmp;

	if (cmd->arg != NULL)
		ft_splitdestroy(cmd->arg);
	if (cmd->line)
		free(cmd->line);
	while (cmd->redir != NULL)
	{
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
		return (ft_strdup(YELLOW));
	if (i % 6 == 1)
		return (ft_strdup(GREEN));
	if (i % 6 == 2)
		return (ft_strdup(CYAN));
	if (i % 6 == 3)
		return (ft_strdup(BLUE));
	if (i % 6 == 4)
		return (ft_strdup(PURPLE));
	else
		return (ft_strdup(RED));
}

void	ft_header(void)
{
	char	*str;
	char	*color;
	int		fd;
	int		i;

	fd = open("data/header.txt", O_RDONLY);
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		color = ft_color(i);
		printf("%s%s", color, str);
		free (str);
		free (color);
		str = get_next_line(fd);
		i++;
	}
	printf("\033[0m\n");
	close (fd);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_head	*head;

	(void)ac;
	(void)av;
	ft_header();
	head = head_init(env);
	if (head == NULL)
		return (0);
	while (42)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		add_history(input);
		if (ft_parse(input, head) == 0)
		{
			executable(head);
			if (head->cmd != NULL)
				ft_free_cmd(head->cmd);
		}
//			while (head->cmd)
//			{
//				printf("line: %s\n", head->cmd->line);
//				tab_display(head->cmd->arg);
//				while (head->cmd->redir)
//				{
//					printf("redir: %s | type: %d\n", head->cmd->redir->arg, head->cmd->redir->type);
//					if (head->cmd->redir->next == NULL)
//						break ;
//					head->cmd->redir = head->cmd->redir->next;
//				}
//				while (head->cmd->redir && head->cmd->redir->prev)
//					head->cmd->redir = head->cmd->redir->prev;
//				if (head->cmd->next == NULL)
//					break ;
//				head->cmd = head->cmd->next;
//			}
//			while (head->cmd->prev)
//				head->cmd = head->cmd->prev;
//		}
	}
	return (ft_free_all(head), 0);
}
