/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:41:07 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/19 18:55:09 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTINS_H
# define MINISHELL_BUILTINS_H

# include "minishell.h"
# include "errno.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>

typedef struct s_env	t_env;
typedef struct s_redir	t_redir;
typedef struct s_cmd	t_cmd;
typedef struct s_fnp	t_fnp;
typedef struct s_head	t_head;


int		ft_cd(t_head *head);
int		ft_cd_bis(t_head *head, char **str);
void	replace_value(t_head *head, char *value, char *replace);
void	cd_no_arg(t_head *head, char **str);
char	*ft_strcat(char *path, char *dir);

void	ft_echo(t_head *head, t_cmd *copy);
void	print_tab(t_head *head, char **arg, int i, int n);

void	ft_env(t_head *head);

void	ft_exit(t_head *head);
int		ft_strnum(char *str);
void	is_num(t_head *head);

int		ft_export(t_head *head);
int		check_name(char *name);
int		ft_strcmp_until(char *s1, const char *s2);
char	*replace_var_until(char *arg, char *result);
int		add_env(t_head *head, char *name, char *value);
//export_utils
int		check_equal(char *str);
char	*dup_until(char *str);
char	*dup_if(char *name, char *value);
int		ft_strlen_until(char *str);
void	free_tab(char **tab);
//built_export_no_arg
char	*join_equal(char *name, char *val);
char	**env_to_tab(t_env *copy);
void	printf_tab(char **tab);
void	swap_this_tab(char **tab);
int		ex_no_args(t_head *head);

void	ft_pwd(t_head *head);
int		get_path(char **str);

void	ft_unset(t_head *head);
void	rem_env(t_env **env, void *ref, int (*cmp)(char *, const char *));
//exec_main
int		find_cmd(t_head *head, t_cmd *copy, t_fnp *fnp, int x);
void	there_cmd(char **arg, char *str, char **env);
int		exec_shell(t_head *head, t_cmd *copy, t_fnp *fnp);
int		executable(t_head *head);

//exec_utils
char	*find_path(t_head *head);
char	*join_with_char(char const *s1, char const *s2, char c);
char	**make_env(t_env *env);

//exec_wait
void	wait_for_all(pid_t *pid, int x);
size_t	envlen(t_env *base);
size_t	cmdlen(t_cmd *base);
char	**redir_arg(t_cmd *cmd, int type);
char	**make_arg(t_cmd *cmd);

//exec_redir
void	fail_malloc(t_head *head, int **fd, size_t i);
int		open_the_pipe(int **fd, t_head *head);
int		open_files(t_redir *redir);
int		open_redir(t_cmd *copy, int fd[2]);

//exec_redir_utils
int		fill_pipe(size_t numb, int **fd, t_head *head);
int		redir_with_fd(int fd[2], int **pipe, t_cmd *copy, int x);
void	close_pipe(t_head *head, int **fd);
void	free_fnp(t_head *head, t_fnp *fnp);
int		malloc_fnp(t_head *head);
//heredoc
void	clear_heredoc_exec(char **arg, char *str, char **env);
int		clear_heredoc(t_head *head);
int		heredoc(t_head *head);

#endif
