#include "pipex.h"
#include "Libft/libft.h"

void	printf_error(const char *name)
{
	perror(name);
	exit(-1);
}

char	*makecmd(char *cmd)
{
	int	i;
	char	*tmp;

	i = 0;
	while (cmd[i] && cmd[i] != 32)
		i++;
	return (ft_substr(cmd, 0, i));
}

char	*get_path(char **av, char **env)
{
	char	*path;

	while (*env && ft_strncmp(*env, "PATH", 4))
		env++;
	*env += 5;
	path = *env;
	return (path);
}

void	exit_error(const char *error, int errorcode)
{
	printf_error(error);
	exit(errorcode);
}

int	ft_listsize(t_cmd *q)
{
	int i = 0;
	while (q)
	{
		i++;
		q = q->next;
	}
	return (i);
}

#include <stdio.h>

int l;
void	run_proccess(t_av t, char **av, char **env, t_cmd *q)
{
	int	fd[2];
	int	i;
	int	size = ft_listsize(q);
	int	status;
	char	buff[200];
	pid_t pid;

	// fd[1] = 입력 // fd[0] = 출력
	i = 0;
	if (pipe(fd) < 0)
		exit_error("pipe Error", -1);
	for (int x = 0; x < 4; x++)
	{
		pid = fork();
		if (pid == 0)
		{
			//dprintf(fd[1], "%d", getpid());
			// printf("pid : %d, ppid : %d", getpid(), getppid());
			printf("?");
			
		}
		else
		{
			// exit(0);
			//printf("pid : %d", getpid());
			printf("p\n");
			wait(&status);
		}
	}
	/* if (pid == 0)
	{
		close(fd[0]);
		dup2(t.infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(t.infile);
		close(fd[1]);
		if (execve(t.infile_cmd, t.parse_cmd1, env) == -1)
			exit_error("command not found", 127);
	}
	else
	{
		wait(&status);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(t.outfile, STDOUT_FILENO);
		close(t.outfile);
		close(fd[0]);
		if (execve(t.outfile_cmd, t.parse_cmd2, env) == -1)
			exit_error("command not found", 127);
	} */
}

void	parse_cmd(t_cmd *t, char **av)
{
	int		i;
	
	i = 2;
	while (t)
	{
		t->parse_cmd = ft_split(av[i], ' ');
		t = t->next;
		i++;
	}
}

char	*get_cmd(char *path, char **env, char *cmd)
{
	char	**split_path;
	char	*cmd_path;
	char	**tmp;
	int		i;
	int		fd;

	cmd = makecmd(cmd);
	split_path = ft_split(path, ':');
	cmd_path = ft_strjoin("/", cmd);
	i = 0;
	while (split_path[i])
	{
		cmd = ft_strjoin(split_path[i], cmd_path);
		fd = access(cmd, X_OK);
		if (!fd)
		{
			free(cmd_path);
			return (cmd);
		}
		free(cmd);
		close(fd);
		i++;
	}
	free(cmd_path);
	return (NULL);
}

void	push_cmd(t_cmd **node, char *cmd)
{
	t_cmd	*tmp;
	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (!tmp)
		exit_error("allocate fail", -1);
	tmp->cmd = cmd;
	tmp->next = NULL;
	if (!*node)
		*node = tmp;
	else
	{
		while ((*node)->next)
			*node = (*node)->next;
		(*node)->next = tmp;
	}
}

t_cmd	*ft_processing_cmd(char *path, char **env, char **av, int ac)
{
	int		i;
	char	*tmp;
	t_cmd	*node;

	i = 2;
	node = NULL;
	while (i < ac - 1)
	{
		tmp = get_cmd(path, env, av[i]);
		if (!tmp)
			exit_error("command not found", 127);
		push_cmd(&node, tmp);
		i++;
	}
	return (node);
}

void	ft_processing(char **av, char **env, int ac)
{
	char	*path;
	t_av	t;
	t_cmd	*node;

	t.infile = open(av[1], O_RDONLY);
	if (t.infile == -1)
		exit_error("Error infile", 1);
	t.outfile = open(av[ac- 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (t.outfile == -1)
		exit_error("Error outfile", 1);
	path = get_path(av, env);
	node = ft_processing_cmd(path, env, av, ac);
	/* t.infile_cmd = get_cmd(path, env, av[2]);
	t.outfile_cmd = get_cmd(path, env, av[3]); */
	/* if (!t.infile_cmd || !t.outfile_cmd)
		exit_error("command not found", 127); */
	parse_cmd(node, av);
	run_proccess(t, av, env, 0);
}

int main(int ac, char **av, char **env)
{
	ft_processing(av, env, ac);
	exit(0);
}