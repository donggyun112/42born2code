/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 03:27:55 by dongkseo          #+#    #+#             */
/*   Updated: 2023/05/12 18:35:42 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <readline/history.h>
#include <readline/readline.h>

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
		{
			ft_putstr_fd("pipex: ", STDERR_FILENO);
			ft_putstr_fd(av[i], STDERR_FILENO);
			exit_error(": command not found", 127, COMMAND_ERROR);
		}
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
		close(t->infile);
		close(t->fd[WRITE]);
		t->infile = t->fd[READ];
	}
}

void	run_proccess(t_av t, char **env, t_cmd *q)
{
	int		status;
	pid_t	pid;

	while (q)
	{
		if (pipe(t.fd) < 0)
			exit_error("pipe Error", -1, EXIT_FAILURE);
		pid = fork();
		if (pid < 0)
			exit_error("fork Error", -1, EXIT_FAILURE);
		do_cmd(pid, q, &t, env);
		q = q->next;
	}
	close(t.outfile);
	close(t.infile);
	close(t.fd[WRITE]);
	close(t.fd[READ]);
	while (waitpid(0, &status, 0) > 0)
		;
}

void	ft_processing_(char **av, char **env, int ac)
{
	char	*path;
	int		error_;
	t_av	t;
	t_cmd	*node;

	t.infile = open(av[1], O_RDONLY);
	error_ = 0;
	if (t.infile == -1)
		error_flag("Error infile", &error_);
	t.outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (t.outfile == -1)
		error_flag("Error outfile", &error_);
	if (error_)
		exit(1);
	t.ac = ac;
	t.flag = !BONUS;
	path = get_path(env);
	node = ft_processing_cmd(path, av, t);
	parse_cmd(node, av, t);
	run_proccess(t, env, node);
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	if (ac < 5)
		return (0);
	if (ft_strcmp("here_doc", av[1]) == 0)
		ft_here_doc_processing(av, env, ac);
	else
		ft_processing_(av, env, ac);
	exit(0);
}

echo -n "hellow world"