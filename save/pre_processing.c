#include "pipex.h"

char	*get_cmd(char *path, char *cmd)
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

char	*makecmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != 32)
		i++;
	return (ft_substr(cmd, 0, i));
}

char	*get_path(char **env)
{
	char	*path;

	while (*env && ft_strncmp(*env, "PATH", 4))
		env++;
	*env += 5;
	path = *env;
	return (path);
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