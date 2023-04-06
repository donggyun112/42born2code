#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_av
{
	int		infile;
	int		outfile;
	int		fd[2];
	int		status;
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


#endif