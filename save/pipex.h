#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_av
{
	int		infile;
	int		outfile;
	int		fd[2];
	int		status;
	int		flag;
	int	ac;
}	t_av;

typedef struct s_cmd
{
	char	*cmd;
	char	**parse_cmd;
	struct	s_cmd *next;
}	t_cmd;

typedef struct s_parse
{
	char	**split_path;
	char	*cmd_path;
}	t_parse;


# define READ 0
# define WRITE 1
# define CHILD 0

# define COMMAND_ERROR 127
# define ERROR			
# define BONUS 1

void	ft_here_doc_processing(char **av, char **env, int ac);
void	init_here_doc_data(t_av *t, char *limits, char **av);
int		ft_strcmp(char *s1, char *s2);
void	ft_processing_(char **av, char **env, int ac);
t_cmd	*ft_processing_cmd(char *path, char **av, t_av t);
void	push_cmd(t_cmd **node, char *cmd);
char	*get_cmd(char *path, char *cmd);
void	free_all(char **str);
void	parse_cmd(t_cmd *t, char **av, t_av q);
void	run_proccess(t_av t, char **env, t_cmd *q);
void	do_cmd(pid_t pid, t_cmd *q, t_av *t, char **env);
void	exit_error(const char *error, int errorcode, int error_status);
char	*get_path(char **env);
char	*makecmd(char *cmd);
void	printf_error(const char *name);

#endif