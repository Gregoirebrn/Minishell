/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:45:32 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/02 21:17:45 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*replace_var_heredoc(char *str, t_head *head)
{
	int		start;
	int		end;
	char	*value;
	char	*dup;

	start = find_var(str);
	end = find_end_var(str, start);
	value = var_value(str, start + 1, head->env);
	if (value == NULL)
		return (NULL);
	dup = str_dup_var(str, start, end, value);
	if (dup == NULL)
		return (NULL);
	return (dup);
}

int	expand_heredoc(char **str, t_head *head)
{
	while (find_var(*str) != -1)
	{
		*str = replace_var_heredoc(*str, head);
		if (*str == NULL)
			return (1);
	}
	return (0);
}

int	here_read_print(int fd, char *eof, t_cmd *copy, t_head *head)
{
	char	*str;

	while (42)
	{
		str = readline(">> ");
		if (!str)
			return (free(str), close(fd), 0);
		//replace strstr by ft_strstr
		if (strstr("^C", str) != NULL)
			return (free(str), close(fd), 2);
		if (ft_strcmp(str, eof) == 0)
			return (free(str), close(fd), 0);
		if (copy->redir->quote == 0)
		{
			if (expand_heredoc(&str, head) == 1)
				return (-1);
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	return (close(fd), 0);
}

int	checker_heredoc(t_head *head, t_redir *c_redir, t_cmd *c_cmd)
{
	int	fd[2];

	if (!c_redir->arg || !c_redir->arg[0])
		return (write(2, "bash: syntax error "\
		"near unexpected token `newline'\n", 51), 0);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit_free(head, 1);
	}
	c_redir->fd = fd[0];
	if (here_read_print(fd[1], c_redir->arg, c_cmd, head))
		return (0);
	return (1);
}

int	heredoc(t_head *head)
{
	t_redir	*c_redir;
	t_cmd	*c_cmd;

	c_cmd = head->cmd;
	while (c_cmd)
	{
		c_redir = head->cmd->redir;
		while (c_redir)
		{
			if (c_redir->type == 4)
			{
				sig_main(head, 2);
				if (checker_heredoc(head, c_redir, c_cmd) == 0)
					return (0);
				sig_main(head, 0);
			}
			c_redir = c_redir->next;
		}
		c_cmd = c_cmd->next;
	}
	return (1);
}
