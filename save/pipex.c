#include "pipex.h"

t_cmd	*ft_processing_cmd(char *path, char **av, t_av t)
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
		tmp = get_cmd(path, av[i]);
		if (!tmp)
			exit_error("command not found", 127, COMMAND_ERROR);
		push_cmd(&node, tmp);
		i++;
	}
	return (node);
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
	path = get_path(env);
	node = ft_processing_cmd(path, av, t);
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