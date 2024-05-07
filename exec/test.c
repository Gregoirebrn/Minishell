#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

char	**ft_split(char const *s, char c);

int		read_fd(int fd)
{
	char	str[200];

	if (-1 == read(fd, str, 200))
		return (perror("read"), 1);
	printf("%s\n", str);
	return (0);
}


char	*ft_strdup(const char *s)
{
	size_t	size;
	size_t	i;
	char	*ptr;

	size = strlen((char *)s);
	ptr = malloc((size + 1) * sizeof(char));
	if (ptr == NULL)
		return (ptr);
	i = 0;
	while (i < size)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

int		main(int ac, char **av, char **env)
{
	int		fd[2];
	int		pid1;
	char	**tab;
	int		pid2;

	tab = NULL;
	if (pipe(fd) == -1)
		return (perror(""), 1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve("/usr/bin/cat", &av[1], env);
		perror("cat");
	}
	tab = malloc(sizeof (char *) * 3);
	tab[0] = ft_strdup("grep");
	tab[1] = ft_strdup("main");
	tab[2] = NULL;
	pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execve("/usr/bin/grep", tab, env);
		perror("grep");
	}
	close(fd[0]);
	close(fd[1]);
	free(tab[0]);
	free(tab);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
