/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:13:37 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/02 22:14:11 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_in_bottom(t_info *a, t_info *b)
{
	pa(a, b);
	ra(a, 1);
	return (0);
}

void	check_odd(t_info *stack_a, t_info *stack_b)
{
	if (stack_a->size % 2 == 1)
	{
		stack_a->is_odd = 0;
		stack_b->is_odd = 0;
	}
	else
	{
		stack_a->is_odd = 1;
		stack_b->is_odd = 1;
	}
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	error_exit(void)
{
	write(2, "Error\n", 6);
	exit(-1);
}
