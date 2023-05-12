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
	int		exit_status;
	int		syntax_error;
}	t_table;

typedef struct s_cmd_info
{
	char	*cmd;
}	t_cmd_info;

char	**ft_split_quote(char const *s, char *c, t_table *table);
static int	check_quote(const char *s);
static int	word_count__(char const *s, char *c, t_table *table);
const char	*quote_string(const char *s, char *c, int *count);
static char	**ft_putstring__(char const *s, char *c, char **arr);
static int	string_len__(char const *s, char *c);
static int	quote_len(char const *s, char *c);
static int	is_quote(char c);
int	is_exist__(char c, char *sep);
static char	**ft_clearall(int j, char **arr);
int	string_len_(char const *s, char *c);
char	**ft_putstring_(char const *s, char *c, char **arr);
int	word_count_(char const *s, char *c);
char	**ft_split_charset(char const *s, char *c);


#define true 1
#define false 0

#endif