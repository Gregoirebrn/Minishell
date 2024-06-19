/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:44:03 by beroy             #+#    #+#             */
/*   Updated: 2024/06/19 14:31:56 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_env	t_env;
typedef struct s_redir	t_redir;
typedef struct s_cmd	t_cmd;
typedef struct s_head	t_head;

// backslash.c

void		remove_backslash(char *str);
void		format_backslash(t_head *head);

// expand_var.c

char		*str_dup_var(char *str, int s, int e, char *val);
int			replace_var_redir(char *str, t_head *head);
int			format_var_redir(t_head *head);
int			format_var(t_head *head);

// expand_var_utils.c

int			find_var(char *str);
int			str_cmp_var(char *str, int i, char *value);
char		*var_value(char *str, int i, t_env *env);
int			find_end_var(char *str, int i);
int			replace_var_line(char *str, t_head *head);

// format_redir.c

void		tab_display(char **tab);
int			spaces_to_add(char *str);
void		ft_dupwithspace2(char *str, char *dup, int i, int j);
char		*ft_dupwithspace(char *str);
int			space_redir(t_cmd *cmd);

// init.c

t_env		*ft_env_new(char *env);
t_env		*ft_envlast(t_env *lst);
void		ft_envadd_back(t_env **lst, t_env *new);
t_env		*env_init(char **env_tab);
t_head		*head_init(char **env);

// init_utils.c

int			find_equal(char *str);
t_redir		*ft_redir_new(char *line, int start, int end, int type);
t_redir		*ft_redirlast(t_redir *lst);
void		ft_rediradd_back(t_redir **lst, t_redir *new);

// parser.c

int			quote_skip(char *input, int *i, char find);
int			str_empty(char *str);
int			check_line(char *input);
t_cmd		*split_pipe(char *input);
int			ft_parse(char *input, t_head *head);

// parser_utils.c

t_cmd		*ft_cmd_new(char *input);
t_cmd		*ft_cmdlast(t_cmd *lst);
void		ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void		find_pipe(char *input, int *i);

// pre_check.c

int			valid_char(char c);
int			check_before(char *input, int checked, int pos);
int			check_after(char *input, int pos);
int			check_redir_pipe(char *input);

// redir.c

int			format_redir(t_cmd *cmd);

// redir_utils.c

int			redir_type(char *line, int i);
int			find_redir(char *line);
int			find_arg(char *line, int start);
char		*dup_without_redir(char *line, int end);
int			extract_redir(t_cmd *cmd);

// split.c

int			ft_countwords(char *input);
int			ft_wdlen(char *input, int j);
char		**split_ws_quote(char *input);
int			split_ws(t_cmd *cmd);

// trim.c

int			nbr_quote(char *str);
void		trim_str_2(char *str, char *trim, int len, int nbr);
char		*trim_str(char *str);
int			trim_tab(char **tab);
int			format(t_head *head);

// utils.c

int			char_is_ws(char c);
void		single_index_up(char *input, int *i);
int			char_is_num(char c);
void		index_up(char *input, int *i);

#endif