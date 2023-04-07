#include "pipex.h"
#include "get_next_line.h"
#include "libft/libft.h"

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

void	exit_error(const char *error, int errorcode, int error_status)
{
	if (error_status == EXIT_FAILURE)
		printf_error(error);
	else
		ft_putstr_fd(error, STDERR_FILENO);
	exit(errorcode);
}

void	do_cmd(pid_t pid, t_cmd *q, t_av *t, char **env)
{
	if (pid == CHILD)
	{
		dup2(t->infile, STDIN_FILENO);
		if (q->next)
			dup2(t->fd[WRITE], STDOUT_FILENO);
		else
			dup2(t->outfile, STDOUT_FILENO);
		close(t->fd[READ]);
		close(t->fd[WRITE]);
		execve(q->cmd, q->parse_cmd, env);
		exit_error("execve Error", -1, EXIT_FAILURE);
	}
	else
	{
		close(t->fd[WRITE]);
		t->infile = t->fd[READ];
	}
}

void	run_proccess(t_av t, char **env, t_cmd *q)
{
	int	status;
	pid_t pid;

	while (q)
	{
		if (pipe(t.fd) < 0)
			exit_error("pipe Error", -1, EXIT_FAILURE);
		pid = fork();
		do_cmd(pid, q, &t, env);
		q = q->next;
	}
	while (wait(&status) > 0)
		;
	close(t.infile);
	close(t.outfile);
}

void	parse_cmd(t_cmd *t, char **av, t_av q)
{
	int		i;
	
	i = 2;
	if (q.flag == BONUS)
		i = 3;
	while (t)
	{
		t->parse_cmd = ft_split(av[i], ' ');
		t = t->next;
		i++;
	}
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

char	*get_cmd(char *path, char **env, char *cmd)
{
	t_parse	t;
	int		i;
	int		fd;

	cmd = makecmd(cmd);
	t.split_path = ft_split(path, ':');
	t.cmd_path = ft_strjoin("/", cmd);
	free(cmd);
	i = 0;
	while (t.split_path[i])
	{
		cmd = ft_strjoin(t.split_path[i], t.cmd_path);
		fd = access(cmd, X_OK);
		if (!fd)
		{
			free_all(t.split_path);
			free(t.cmd_path);
			return (cmd);
		}
		free(cmd);
		close(fd);
		i++;
	}
	free(t.cmd_path);
	free_all(t.split_path);
	return (NULL);
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

t_cmd	*ft_processing_cmd(char *path, char **env, char **av, t_av t)
{
	int		i;
	char	*tmp;
	t_cmd	*node;

	i = 2;
	if (t.flag == BONUS)
		i = 3;
	node = NULL;
	while (i < t.ac - 1)
	{
		tmp = get_cmd(path, env, av[i]);
		if (!tmp)
			exit_error("command not found", 127, COMMAND_ERROR);
		push_cmd(&node, tmp);
		i++;
	}
	return (node);
}

void	ft_processing_(char **av, char **env, int ac)
{
	char	*path;
	t_av	t;
	t_cmd	*node;

	t.infile = open(av[1], O_RDONLY);
	if (t.infile == -1)
		exit_error("Error infile", 1, EXIT_FAILURE);
	t.outfile = open(av[ac- 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (t.outfile == -1)
		exit_error("Error outfile", 1, EXIT_FAILURE);
	t.ac = ac;
	t.flag = !BONUS;
	path = get_path(av, env);
	node = ft_processing_cmd(path, env, av, t);
	parse_cmd(node, av, t);
	run_proccess(t, env, node);
	exit(0);
}

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

void	init_here_doc_data(t_av *t, char *limits, char **av)
{
	int		fd;
	char	*line;

	fd = open("tmp", O_WRONLY | O_CREAT | O_EXCL |O_TRUNC, 0600);
	t->infile = dup(fd);
	while (1)
	{
		line = get_next_line(0);
		write(t->infile, line, ft_strlen(line));
		if(ft_strncmp(line, limits, ft_strlen(limits)) == 0)
			break ;
		free(line);
	}
	close(t->infile);
	t->infile = open("tmp", O_RDONLY);
	close(fd);
	unlink("tmp");
	t->outfile = open(av[t->ac- 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (t->outfile == -1)
		exit_error("Error outfile", 1, EXIT_FAILURE);
}

void	ft_here_doc_processing(char **av, char **env, int ac)
{
	t_av	t;
	t_cmd *node;
	char	*path;

	t.ac = ac;
	t.flag = BONUS;
	init_here_doc_data(&t, av[2], av);
	path = get_path(av, env);
	node = ft_processing_cmd(path, env, av, t);
	parse_cmd(node, av, t);
	run_proccess(t, env, node);
	exit(0);
}

int main(int ac, char **av, char **env)
{
	if (ft_strcmp("here_doc", av[1]) == 0)
		ft_here_doc_processing(av, env, ac);
	else
		ft_processing_(av, env, ac);
	exit(0);
}