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
	int	infile;
	int	outfile;
	char	*infile_cmd;
	char	*outfile_cmd;
	char	**parse_cmd1;
	char	**parse_cmd2;
}	t_av;

typedef struct s_cmd
{
	char	*cmd;
	char	**parse_cmd;
	struct	s_cmd *next;
}	t_cmd;


#endif