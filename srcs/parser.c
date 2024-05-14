/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:19:51 by beroy             #+#    #+#             */
/*   Updated: 2024/05/13 16:50:49 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quote_skip(char *input, int *i, char find)
{
	*i += 1;
	while (input[*i] != 0 && input[*i] != find)
		*i += 1;
	if (input[*i] == 0)
		return (1);
	return (0);
}

int check_line(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
				return (printf("double pipe not handled by minishell!\n"), 1);
		}
		else if (input[i] == 34)
		{
			if (quote_skip(input, &i, 34) == 1)
				return (printf("Quote unterminated!\n"), 1);
		}
		else if (input[i] == 39)
		{
			if (quote_skip(input, &i, 39) == 1)
				return (printf("Quote unterminated!\n"), 1);
		}
		i++;
	}
	return (0);
}

t_cmd	*split_pipe(char *input)
{
	t_cmd	*cmd;
	t_cmd	*new;
	char	*extract;
	int offset;
	int i;

	offset = 0;
	i = 0;
	cmd = NULL;
	while (input[i])
	{
		find_pipe(input, &i);
		extract = ft_substr(input, offset, i - offset);
		if (extract == NULL)
			return (ft_free_cmd(cmd), NULL);
		new = ft_cmd_new(extract);
		if (new == NULL)
			return (ft_free_cmd(cmd), NULL);
		ft_cmdadd_back(&cmd, new);
		i++;
		offset = i;
	}
	return (cmd);
}

int	ft_parse(char *input, t_head *head)
{
	if (check_line(input) == 1)
		return (1);
	// split par rapport au pipe - un bloc par maillon de la liste
	head->cmd = split_pipe(input);
	if (head->cmd == NULL)
		return (1);
	// Add spaces before and after redirs
	if (space_redir(head->cmd) == 1)
		return (1);
	// sortir les redirections de line et les stocker dans la struct redir
	if (format_redir(head->cmd) == 1)
		return (1);
	// Transformer les $variables par leur valeur
	if (format_var(head) == 1)
		return (1);
	// split dans chaque bloc par rapport au whitespaces
	if (split_ws(head->cmd) == 1)
		return (1);
	// format le contenu des blocs - redirection + variable env etc
	return (0);
}
