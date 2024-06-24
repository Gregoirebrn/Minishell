/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:24:43 by beroy             #+#    #+#             */
/*   Updated: 2024/06/11 17:47:56 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../super_libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "builtins.h"
# include "parser.h"

// COLOR CODES

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"

extern int	g_error;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_redir
{
	int				type;
	int				fd;
	char			*arg;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_cmd
{
	char 			*line;
	char			**arg;
	t_redir			*redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_fnp
{
	int	*pid;
	int	**pipe;
}	t_fnp;

typedef struct s_head
{
	t_cmd	*cmd;
	t_env	*env;
	t_fnp	*fnp;
}	t_head;

// main.c

void	ft_free_cmd(t_cmd *cmd);
void	ft_free_all(t_head *head);

//signal
void	sig_main(t_head *head, int sig_val);

#endif
