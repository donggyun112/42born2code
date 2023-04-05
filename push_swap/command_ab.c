/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:46:52 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/03 23:34:35 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rr(t_info *stack_a, t_info *stack_b)
{
	if (!stack_a->head || !stack_b->head)
		return ;
	if (!stack_a->head->next || !stack_b->head->next)
		return ;
	ra(stack_a, FALSE);
	rb(stack_b, FALSE);
	if (!stack_a->run_checker)
		ft_putstr("rr\n");
}

void	ss(t_info *stack_a, t_info *stack_b)
{
	if (!stack_a->run_checker)
		ft_putstr("ss\n");
	if (!stack_a || stack_a->size < 2)
		return ;
	if (!stack_b || stack_b->size < 2)
		return ;
	sa(stack_a, FALSE);
	sb(stack_b, FALSE);
}

void	rrr(t_info *stack_a, t_info *stack_b)
{
	if (!stack_a->run_checker)
		ft_putstr("rrr\n");
	rra(stack_a, FALSE);
	rrb(stack_b, FALSE);
}
