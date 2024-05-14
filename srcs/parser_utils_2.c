/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:18:25 by beroy             #+#    #+#             */
/*   Updated: 2024/04/25 14:13:44 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int char_is_ws(char c)
{
	if ((c > 7 && c < 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_countwords(char *input)
{
	int	i;
	int wds;

	wds = 0;
	i = 0;
	if (char_is_ws(input[i]) == 0 && input [i])
		wds++;
	index_up(input, &i);
	while (input[i])
	{
		if (char_is_ws(input[i]) == 0 && char_is_ws(input[i - 1]) == 1)
			wds++;
		index_up(input, &i);
	}
	return (wds);
}

int	ft_wdlen(char *input, int j)
{
	int	i;

	i = j;
	while (char_is_ws(input[i]) == 0 && input[i])
		index_up(input, &i);
	return (i);
}

static char	*ft_superdup(char *s, int *j)
{
	char	*str;
	int	len;
	int	i;

	len = ft_wdlen(s, *j);
	str = malloc(sizeof(char) * (len - *j + 1));
	if (str == NULL)
		return (str);
	i = 0;
	while (*j < len)
	{
		str[i] = s[*j];
		*j += 1;
		i++;
	}
	str[i] = 0;
	return (str);
}

char	**split_ws_quote(char *input)
{
	int		i;
	int		j;
	int		words;
	char	**split;

	i = 0;
	j = 0;
	words = ft_countwords(input);
	split = ft_calloc(words + 1, sizeof(char*));
	if (split == NULL)
		return (NULL);
	while (i < words)
	{
		if (char_is_ws(input[j]) == 0)
		{
			split[i] = ft_superdup(input, &j);
			if (split[i] == NULL)
				return (ft_splitdestroy(split));
			i++;
		}
		else
			index_up(input, &j);
	}
	return (split);
}

int split_ws(t_cmd *cmd)
{
	while (cmd->next)
	{
		cmd->arg = split_ws_quote(cmd->line);
		if (cmd->arg == NULL)
			return (1);
		cmd = cmd->next;
	}
	cmd->arg = split_ws_quote(cmd->line);
	if (cmd->arg == NULL)
		return (1);
	rewind_cmd(cmd);
	return (0);
}
