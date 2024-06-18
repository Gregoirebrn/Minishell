/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:45:32 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/18 17:19:00 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_heredoc_exec(char **arg, char *str_of_path, char **env)
{
	char	**path;
	int		i;
	char	*cmd;

	path = ft_split(str_of_path, ':');
	i = 0;
	while (path[i])
	{
		cmd = join_with_char(path[i], arg[0], '/');
		if (!(access(cmd, F_OK)) && !(access(cmd, X_OK)))
			execve(cmd, arg, env);
		i++;
	}
	g_error = 127;
	perror(arg[0]);
	exit (2);
}

int	clear_heredoc(t_head *head)
{
	char	**env;
	char	**arg;
	char	*path;

	while (head->cmd)
	{
		if (head->cmd->redir && head->cmd->redir->type == 4)
			break;
		head->cmd = head->cmd->next;
	}
	if (!head->cmd->redir)
		return (0);
	env = make_env(head->env);
	arg = redir_arg(head->cmd, 1);
	path = find_path(head);
	if (!path)
		return (free_tab(arg), free_tab(env), ft_free_all(head), 1);
	clear_heredoc_exec(arg, path, env);
	return (0);
}

int	heredoc(t_head *head)
{
	char	*str;
	char	*eof;

	str = NULL;
	if (!(head->cmd->redir && head->cmd->redir->type == 4))
		return (0);
	//doesn't work do to parsing exiting before
	if (!head->cmd->redir->arg)
		return (ft_printf_fd(2, "bash: syntax error near unexpected token `newline'"), -1);
	//create tmp file
	head->cmd->redir->fd = open("tmp", O_WRONLY | O_CREAT, 0644);
	eof = head->cmd->redir->arg;
	while (42)
	{
		str = readline("> ");
		if (!str)
			return (write(2, "Error readline\n", 15), -1);
		if (ft_strcmp(str, eof) == 0)
		{
			free(str);
			break;
		}
		write(head->cmd->redir->fd, str, ft_strlen(str));
		write(head->cmd->redir->fd, "\n", 1);
		free(str);
		//add to pipe
	}
//	head->cmd->redir->fd = 1;
	return (1);
	//verifier le EOF si il est avec ou sans ""
	//gestion d'erreurs
}
