#include "test.h"
#include "get_next_line.h"
#include "get_next_line.c"
#include "get_next_line_utils.c"
#include "test.c"
#include <stdio.h>

void	check_command(const char *line, t_info *a, t_info *b)
{
	if (!ft_strcmp("pa\n", line))
		pa(a, b);
	else if (!ft_strcmp("pb\n", line))
		pb(a, b);
	else if (!ft_strcmp("ra\n", line))
		ra(a, 0);
	else if (!ft_strcmp("rb\n", line))
		rb(b, 0);
	else if (!ft_strcmp("rra\n", line))
		rra(a, 0);
	else if (!ft_strcmp("rrb\n", line))
		rrb(b, 0);
	else if (!ft_strcmp("rrr\n", line))
		rrr(a, b);
	else if (!ft_strcmp("rr\n", line))
		rr(a, b);
	else if (!ft_strcmp("sa\n", line))
		sa(a, 0);
	else if (!ft_strcmp("sb\n", line))
		sb(b, 0);
	else if (!ft_strcmp("ss\n", line))
		ss(a, b);
	else
		error_exit();
}
#include <stdio.h>
int main(int ac, char **av)
{
	t_info	*stack_a;
	t_info	*stack_b;
	char	*line;

	if (ac < 2)
		return (-1);
	set_list(&stack_a, 'a');
	stack_a->run_checker = 1;
	ft_init(stack_a, ac, av);
	set_list(&stack_b, 'b');
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		check_command(line, stack_a, stack_b);
		free(line);
	}
	is_sorted(stack_a);
	ft_putstr("KO\n");
	exit(0);
}