/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:41:07 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/13 15:31:44 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTINS_H
#define MINISHELL_BUILTINS_H

#include "minishell.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_env t_env;
typedef struct s_redir t_redir;
typedef struct s_cmd t_cmd;
typedef struct s_head t_head;

//builtins00
void	ft_echo(t_head *head, int fd);
void	ft_pwd(void);
int		ft_cd(t_head *head);
int		ft_export(t_head *head);
void	ft_unset(t_head *head);

//bultins01
char	*ft_strcat(char *path, char *dir);
int		get_path(char **str);
void	rem_env(t_env **env, void *ref, int (*cmp)(char *, const char *));
void	ft_env(t_head *head);

//bultins02
void	change_old_pwd(t_head *head, char *old_pwd);
void	replace_var(char **arg, char *result);
int		add_env(t_head *head, char *name, char *value);
void	print_tab(char **arg, int i, int n, int fd);

//built_exit
void	ft_exit(t_head *head);

//export_no_args
void	free_tab(char **tab, size_t x);
char	**env_to_tab(t_env *copy);
int		ex_no_args(t_head *head);

//piping00
int		find_cmd(t_head *head, t_cmd *copy, int fd[2], int *pid);
void	there_cmd(char **arg, char *str, char **env);
int		make_child(t_head *head, int fd[2]);
int		executable(t_head *head);

//piping01
char	**path_value(t_head *head);
char	*find_path(t_head *head);
char	*join_with_char(char const *s1, char const *s2, char c);
char	**make_env(t_env *env);

//piping02
void	wait_for_all(pid_t *pid, int x);
size_t	envlen(t_env *base);
size_t	cmdlen(t_cmd *base);
char	**make_arg(t_cmd *cmd);
void	ft_free_exec(int **fd, int *pid, t_head *head);

//piping03
void	dup_of_fd(int fd[2], t_cmd *copy);

#endif
