#include "pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	printf_error(const char *name)
{
	perror(name);
	exit(-1);
}

void	exit_error(const char *error, int errorcode, int error_status)
{
	if (error_status == EXIT_FAILURE)
		printf_error(error);
	else
		ft_putstr_fd(error, STDERR_FILENO);
	exit(errorcode);
}

void	push_cmd(t_cmd **node, char *cmd)
{
	t_cmd	*tmp;
	t_cmd	*head;
	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (!tmp)
		exit_error("allocate fail", -1, EXIT_FAILURE);
	tmp->cmd = cmd;
	tmp->next = NULL;
	if (!*node)
		*node = tmp;
	else
	{
		head = *node;
		while (head->next)
			head = head->next;
		head->next = tmp;
	}
}