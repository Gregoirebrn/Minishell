#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

static size_t	ft_countwords(char const *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	if (s[i] != c && s[i] != 0)
		words++;
	i++;
	while (s[0] && s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			words++;
		i++;
	}
	return (words);
}

static size_t	ft_wdlen(char const *s, char c, size_t j)
{
	size_t	i;

	i = j;
	while (s[i] != c && s[i] != 0)
		i++;
	return (i);
}

static char	*ft_superdup(char const *s, char c, size_t *j)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_wdlen(s, c, *j);
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

static void	*ft_splitdestroy(char **split)
{
	size_t	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	words;
	char	**split;

	/*if (!s)
	  return (NULL);*/
	i = 0;
	j = 0;
	words = ft_countwords(s, c);
	split = calloc((words + 1), sizeof(char *));
	if (!s[0] || split == NULL)
		return (split);
	while (i < words)
	{
		if (s[j] != c)
		{
			split[i++] = ft_superdup(s, c, &j);
			if (split[i - 1] == NULL)
				return (ft_splitdestroy(split));
		}
		else
			j++;
	}
	return (split);
}

int		get_path(char **str)
{
	size_t	size;

	size = 10;
	while (!*(str))
	{
		*str = getcwd(*(str), size);
		if (!*(str))
		{
			free(*(str));
			*(str) = NULL;
			if (errno != ERANGE)
				return (2);
		}
		size += 10;
	}
	return (0);
}

char	*change_old_pwd(char *old_pwd)
{
	char *copy;

	copy = NULL;
	get_path(&copy);
	free(copy);
	copy = old_pwd;
	printf("%s", copy);
	return (copy);
}
void	replace_var(char **arg, char *str, char *result)
{
	int		i;
	int		x;
	int		z;

	free(arg[i]);
	arg[i] = calloc((strlen(str) + strlen(result) + 2), sizeof (char));
	x = 0;
	while (arg[i][x] && str[x])
	{
		arg[i][x] = str[x];
		x++;
	}
	arg[i][x++] = '=';
	z = 0;
	while (result[z])
	{
		arg[i][x] = result[z];
		z++;
		x++;
	}
	arg[i][x] = '\0';
}

//void	ft_export(t_head *head)
//{
//	int	i;
//
//	i = 0;
//	while (head->[i])
//	{
//		if (0 == strncmp(arg[i], str, strlen(str)))
//		{
//			replace_var(arg, str, result);
//				return ;
//		}
//		i++;
//	}
//}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*str;

	len = strlen((char *)s1) + strlen((char *)s2);
	i = 0;
	str = malloc (sizeof(char) * (len + 2));
	if (str == NULL)
		return (str);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '/';
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str [i + j] = 0;
	return (str);
}

int	ft_strncmp(char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != 0 || s2[i] != 0) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != 0 || s2[i] != 0)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		main(int ac, char **av, char **env)
{
	int		fd[2];
	int		pid1;

	if (pipe(fd) == -1)
		return (perror(""), 1);
	pid1 = fork ();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve("usr/bin/cat", av, env);
	}
	waitpid(fd[1], NULL, 0);
	waitpid(fd[1], NULL, 0);
}
