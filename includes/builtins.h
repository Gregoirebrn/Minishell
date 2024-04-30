/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:41:07 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/30 18:51:02 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTINS_H
#define MINISHELL_BUILTINS_H

#include "errno.h"
#include "minishell.h"

typedef struct s_env t_env;
typedef struct s_redir t_redir;
typedef struct s_cmd t_cmd;
typedef struct s_head t_head;

char	*ft_strcat(char *path, char *dir);
int		get_path(char **str);
void	rem_env(t_env **env, void *ref, int (*cmp)(char *, const char *, size_t));
void	change_old_pwd(t_head *head, char *old_pwd);
void	replace_var(char **arg, char *result);

void	ft_echo(t_head *head);
void	ft_pwd(void);
int		ft_cd(t_head *head);
int		ft_export(t_head *head);
void	ft_unset(t_head *head);
void	ft_env(t_head *head);
void	ft_exit(t_head *head);

int		our_cmd(t_head *head, char *str);
void	find_cmd(t_head *head);
char	**path_value(t_head *head);
char	*find_path(t_head *head);
char	*join_with_char(char const *s1, char const *s2, char c);
size_t	len_struct(void *base);
int		ex_no_args(t_head *head);
int		add_env(t_head *head, char *name, char *value);
char	**make_env(t_env *env);
void	wait_for_all(pid_t *pid, int x);

#endif
