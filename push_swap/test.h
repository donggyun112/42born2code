# ifndef TEST_H
# define TEST_H

# include <stdlib.h>

typedef struct s_list
{
	int data;
	struct s_list *next;
	struct s_list *prev;
}	t_list;

typedef struct s_info
{
	int	size;
	struct s_list *head;
	struct s_list *tail;
}	t_info;

#endif