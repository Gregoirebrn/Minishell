/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:53:49 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/02 21:24:04 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig(int sig)
{
	if (sig == SIGINT)
	{
		g_error = 130;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_child(int sig)
{
	if (sig == SIGPIPE)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (sig == SIGINT)
	{
		g_error = 130;
		write(2, "\n", 1);
	}
	if (sig == SIGQUIT)
	{
		g_error = 131;
		write(2, "Quit (core dumped)\n", 19);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_error = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		close_pipe();
	}
}

void	sig_main(t_head *head, int sig_val)
{
	if (SIG_ERR == signal(SIGINT, SIG_IGN))
		ft_exit(head);
	if (SIG_ERR == signal(SIGQUIT, SIG_IGN))
		ft_exit(head);
	if (sig_val == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &sig);
	}
	else if (sig_val == 1)
	{
		signal(SIGQUIT, &sig_child);
		signal(SIGPIPE, &sig_child);
		signal(SIGINT, &sig_child);
	}
	else if (sig_val == 2)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &sig_heredoc);
	}
}
