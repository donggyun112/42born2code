/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:25:37 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/04 01:48:59 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef struct s_list
{
	int				data;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_info
{
	int				size;
	int				is_odd;
	int				run_checker;
	int				is_end;
	char			name;
	struct s_list	*head;
	struct s_list	*tail;
}	t_info;

typedef struct s_count
{
	int	count_ra;
	int	count_rb;
	int	count_push;
	int	pivot1;
	int	pivot2;

}	t_count;

typedef struct s_check
{
	char	**split_tmp;
	char	*itoa_tmp;
	int		data;
}	t_check;

typedef struct s_merge
{
	int	left_size;
	int	right_size;
	int	*left;
	int	*right;
}	t_merge;

//sort
void	merge_sort(int *arr, int size);
void	merge(int arr[], int left[], t_merge t, int right[]);

//num
int		ft_atoi(const char *str);
int		nb_len(long long nb);
void	write_int(long long nb, char *arr, int *lev);
char	*ft_itoa(int n);

//command_a
int		pa(t_info *stack_a, t_info *stack_b);
void	sa(t_info *stack_a, int flag);
void	rra(t_info *stack_a, int flag);
int		ra(t_info *stack_a, int flag);
//command_b
int		pb(t_info *stack_a, t_info *stack_b);
int		rb(t_info *stack_b, int flag);
void	rrb(t_info *stack_b, int flag);
void	sb(t_info *stack_b, int flag);
//command_ab
void	rr(t_info *stack_a, t_info *stack_b);
void	ss(t_info *stack_a, t_info *stack_b);
void	rrr(t_info *stack_a, t_info *stack_b);
//list_command
void	push_front(t_info *node, int data);
void	push(t_info *stack_a, int data);
void	pop_back(t_info *stack);
void	pop_front(t_info *stack);

//init_data
void	ft_init(t_info *stack, int ac, char **av);
int		ft_in_bottom(t_info *a, t_info *b);

//check_val
void	ft_init_split_data(t_info *stack, t_check *t);
void	check_duble(t_info *stack);
void	is_sorted(t_info *stack);
int		ft_strcmp(const char *s1, const char *s2);

// set
void	set_list(t_info **node, char name);
void	set_count(t_count *t);

//sort_tools
int		sort_two(t_info *stack);
void	sort_three(t_info *a);
void	sort_revers_two(t_info *stack);
void	sort_revers_three(t_info *b);

//sort
int		sort_five(t_info *a, t_info *b);
void	sort_a(t_info *a, int cnt);
void	sort_b(t_info *a, t_info *b, int cnt);
int		simplesort(t_info *a);

//tools
void	__push(t_info *s1, t_info *s2, int cnt);
void	revers_stack(t_info *a, t_info *b, int ra, int rb);
int		t_d(t_info *stack);
int		tp_d(t_info *stack);
int		tpp_d(t_info *stack);

//solve
void	b_to_a(t_info *a, t_info *b, int cnt);
void	a_to_b(t_info *a, t_info *b, int cnt);
void	get_pivot(int *p1, int *p2, t_info *a, int size);

//utils
void	check_odd(t_info *stack_a, t_info *stack_b);
void	ft_putstr(char *str);
void	error_exit(void);

// split
int		string_len(char const *s, char c);
char	**ft_clearall(int j, char **arr);
char	**ft_putstring(char const *s, char c, char **arr);
int		word_count(char const *s, char c);
char	**ft_split(char const *s, char c);

//bonus
void	check_command(const char *line, t_info *a, t_info *b);
int		ft_strlen(char *str);
char	*ft_strjoin(const char *s1, char const *s2);
char	*ft_strcat(char *string1, const char *string2);
char	*ft_strchr(const char *string, int c);
char	*ft_strdup_v2(const char *string, int *start, int *flag);
char	*ft_processing(int fd, int *start, int *flag, char **stack);
char	*get_next_line(int fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2561
# endif

#endif
