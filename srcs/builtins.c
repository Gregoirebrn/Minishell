/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:30:25 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/18 16:28:35 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//echo a tester

void	ft_echo(t_head *head)
{
	t_cmd	*copy;
	int		i;

	i = 0;
	copy = head->cmd;
	while (copy->next != NULL)
	{
		if (i == 1 &&  0 == ft_strncmp(copy->arg[i], "-n", ft_strlen(copy->arg[i])))
			i = -1;
		printf("%s ", copy->arg[i]);
		copy = copy->next;
		if (i > -1)
			i++;
	}
	if (0 == ft_strncmp(copy->arg[i], "-n", ft_strlen(copy->arg[i])))
		printf("%s", copy->arg[i]);
	else
		printf("%s\n", copy->arg[i]);
}

void	ft_pwd(void)
{
	int		err;
	char	*str;

	str = NULL;
	err = get_path(&str);
	if (err == 2)
	{
		write(1, "bash: pwd: ", 10);
		perror(str);
	}
	printf("%s\n", str);
	free(str);
}

int	ft_cd(t_head *head)

{
	int		err;
	char	*str;
	int		len;

	str = NULL;
	get_path(&str);
	str = ft_strcat(str, head->cmd->arg[1]);
	if (str == NULL)
		return (printf("Crash of Malloc\n"), 2);
	err = chdir(str);
	free(str);
	if (err != 0)
		return (write(1, "bash: cd: ", 10), perror(head->cmd->arg[1]), 2);
	return (0);
}

void	ft_export(t_head *head)
{
	char *str;

	str = getenv(head->cmd->arg[1]);
	if (str == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	printf("%s\n", str);
}

void	rem_env(t_env **env, void *ref, int (*cmp)(char *, const char *, size_t))
{
	t_env	*remove;
	t_env	*current;

	current = *env;
	while (current && current->next)
	{
		if ((*cmp)(current->next->name, ref, ft_strlen(ref)) == 0)
		{
			remove = current->next;
			current->next = current->next->next;
			free(remove);
		}
		current = current->next;
	}
	current = *env;
	if (current && (*cmp)(current->name, ref, ft_strlen(ref)) == 0)
	{
		*env = current->next;
		free(current);
	}
}

void	ft_unset(t_head *head)
{
	rem_env(&head->env, head->cmd->arg[1], &ft_strncmp);
}
