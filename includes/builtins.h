/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:41:07 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/12 19:42:44 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTINS_H
#define MINISHELL_BUILTINS_H

#include "minishell.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

typedef struct s_env t_env;
typedef struct s_redir t_redir;
typedef struct s_cmd t_cmd;
typedef struct s_head t_head;

//builtins00
void	ft_echo(t_head *head, t_cmd *copy);
void	ft_pwd(t_head *head);
int		ft_cd(t_head *head);
int		ft_export(t_head *head);
void	ft_unset(t_head *head);

//bultins01
char	*ft_strcat(char *path, char *dir);
int		get_path(char **str);
void	rem_env(t_env **env, void *ref, int (*cmp)(char *, const char *));
void	ft_env(t_head *head);

//bultins02
void	replace_value(t_head *head, char *value, char *replace);
void	replace_var(char **arg, char *result);
int		add_env(t_head *head, char *name, char *value);
void	print_tab(char **arg, int i, int n);
void	cd_no_arg(t_head *head, char **str);

//bultins03
int		ft_cd_bis(t_head *head, char **str);
void	free_tab(char **tab, size_t x);
char	*dup_until(char *str);
char	*dup_if(char *name, char *value);
int		ft_strcmp_until(char *s1, const char *s2);

//builtins04
int		check_name(char *name);
int		ft_strlen_until(char *str);
void	replace_var_until(char **arg, char *result);

//built_exit
void	ft_exit(t_head *head);

//export_no_args
char	*join_equal(char *name, char *val);
char	**env_to_tab(t_env *copy);
void	printf_tab(char **tab);
void	swap_this_tab(char **tab);
void	ex_no_args(t_head *head);

//piping00
int		find_cmd(t_head *head, t_cmd *copy, int **fd, int x);
void	there_cmd(char **arg, char *str, char **env);
int		exec_shell(t_head *head, t_cmd *copy);
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
void	free_pipe(int **fd, t_head *head);
void	fail_malloc(int **fd, size_t i);
int		open_the_pipe(int **fd, t_head *head);
int		open_files(t_redir *redir);
int		open_redir(t_cmd *copy, int fd[2]);

//piping04
int		fill_fd(size_t numb, int **fd, t_head *head);
int		redir_with_fd(int fd[2], int **pipe, t_cmd *copy, int x);
void	close_pipe(t_head *head, int **fd);


#endif
