#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

size_t ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

void	ft_strcat(char *s1, char *s2)
{
	if (!s1 || !s2)
		return ;
	while (*s1)
		s1++;
	while (*s2)
		*s1++ = *s2++;
	*s1 = '\0';
}

char *ft_strjoin(char *buff, char *stack)
{
	int len1 = 0;
	int len2 = 0;
	char *result;
	len1 = ft_strlen(buff);
	len2 = ft_strlen(stack);
	result = (char *)malloc(sizeof(char) * len1 + len2 + 100);
	result[0] = '\0';
	if (!result)
		return (NULL);
	ft_strcat(result, buff);
	ft_strcat(result, stack);
	return (result);
}

int ft_strchr(char *buff)
{
	while (*buff)
	{
		if (*buff == '\n')
			return (1);
		buff++;
	}
	return (0);
}

char *ft_strdup(char *stack, int *st)
{
	size_t len = 0;
	char *ret;
	ret = (char *)malloc(sizeof(char) * len + 100);
	len = ft_strlen(stack);
	int i = 0;
	while (stack[i] && stack[i] != '\n')
	{
		ret[i] = stack[i];
		i++;
		(*st)++;
	}
	if (stack[i] == '\0')
		*st = 0;
	if (stack[i] == '\n')
	{
		*st += 1;
		ret[i] = '\n';
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char *get_result(int fd, char **stack, int *st)
{
	char buff[BUFFER_SIZE + 1];
	int rd_size;
	char *tmp;

	if (!stack)
		return (NULL);
	while ((rd_size = read(fd, buff, BUFFER_SIZE)))
	{
		if (rd_size < 0)
			return (NULL);
		buff[rd_size] = '\0';
		tmp = ft_strjoin(buff, *stack);
		if (tmp)
		{
			free(*stack);
			*stack = tmp;
			tmp = NULL;
		}
		else
			return (NULL);
		if (ft_strchr(buff))
			break ;
	}
	return (ft_strdup(*stack + *st, st));
}

char *get_next_line(int fd)
{
	static char	*stack;
	static int st;
	char *tmp;

	tmp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stack)
	{
		stack = (char *)malloc(sizeof(char) * 100);
		*stack = '\0';
	}
	tmp = get_result(fd, &stack, &st);
	if (!tmp || st == 0)
	{
		free(stack);
		st = 0;
		stack = NULL;
	}
	if (tmp && !*tmp)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
#include <stdio.h>
int main(int ac, char **av)
{
	if (ac < 2)
		return (0);
	char *str = av[1];
	int fd;
	fd = open(str, O_RDONLY);
	char *tmp;
	while ((tmp = get_next_line(fd)))
	{
		printf("%s", tmp);
	}
}

