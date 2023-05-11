#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include "libft/libft.h"
# include <stdlib.h>

typedef struct	s_table
{
	char	**envp;
}	t_table;

#define true 1
#define false 0

#endif

// ft_putstr_fd("\033[12C", STDOUT_FILENO);