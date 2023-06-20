#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void	ft_putstr_fd2(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	write(2, str, i);
}

int	ft_execute(char **argv, int i, int tmp_fd, char **env)
{
	argv[i] = NULL;
	close(tmp_fd);
	execve(argv[0], argv, env);
	ft_putstr_fd2("error\n");
	return (1);
}

int main(int ac, char **argv, char **env)
{
	int pid, fd[2], i, tmp_fd;

	pid = 0;
	i = 0;
	tmp_fd = dup(0);
	while (argv[i] && argv[i + 1])
	{
		argv = &argv[i + 1]; // 포인트
		i = 0;
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (strcmp(argv[0], "cd") == 0)
		{
			if (i != 2)
				ft_putstr_fd2("error: cd \n");
			else if (chdir(argv[1]) != 0)
				ft_putstr_fd2("error change\n");
		}
		else if (argv != &argv[i] && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(tmp_fd, 0);
				if (ft_execute(argv, i, tmp_fd, env))
					return (1);
			}
			else
			{
				close(tmp_fd);
				waitpid(-1, 0, 0);
				tmp_fd = dup(0);
			}
		}
		else if(argv != &argv[i] && strcmp(argv[i], "|") == 0)
		{
			pipe(fd); // 이거 순서 중요함
			pid = fork(); // 이거 순서중요함
			if (pid == 0)
			{
				dup2(tmp_fd, 0);
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
				if (ft_execute(argv, i, tmp_fd, env))
					return (1);
			}
			else
			{
				close(fd[1]);
				close(tmp_fd);
				waitpid(-1, 0, 0);
				tmp_fd = dup(fd[0]);
				close(fd[0]);
			}
		}
	}
	close(tmp_fd);
	return (0);
}