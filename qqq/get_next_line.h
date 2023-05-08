#ifndef GET_NEXt_LINE_H
# define GET_NEXt_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

typedef struct s_tools
{
	char 		*backup;
	int			rd;
} t_tools;

typedef struct s_tmp
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	buff[BUFFER_SIZE + 1];
} t_tmp;

size_t	ft_strlen(char *str);
char	*ft_strchr(const char *string, int c);
char	*ft_strcat(char *string1, const char *string2);
char	*ft_strjoin(const char *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);


#endif