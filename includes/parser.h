/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:44:03 by beroy             #+#    #+#             */
/*   Updated: 2024/04/18 17:22:25 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_env	t_env;
typedef struct s_redir	t_redir;
typedef struct s_cmd	t_cmd;
typedef struct s_head	t_head;

// init.c

t_head	*head_init(void);

// parser.c

t_cmd	*ft_parse(char *input, t_head *head);

#endif