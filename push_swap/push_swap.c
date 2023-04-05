/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 23:03:34 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/04 01:55:55 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	leaks(void)
{
	system("leaks push_swap");
}

int	main(int ac, char **av)
{
	t_info	*stack_a;
	t_info	*stack_b;

	if (ac < 2)
		return (-1);
	set_list(&stack_a, 'a');
	stack_a->run_checker = 0;
	ft_init(stack_a, ac, av);
	is_sorted(stack_a);
	set_list(&stack_b, 'b');
	stack_a->is_end = 0;
	check_odd(stack_a, stack_b);
	if (stack_a->size == 3)
		simplesort(stack_a);
	else if (stack_a->size == 5)
		sort_five(stack_a, stack_b);
	else
		a_to_b(stack_a, stack_b, stack_a->size);
	exit(0);
}
