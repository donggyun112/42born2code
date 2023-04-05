/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:00:24 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/02 22:15:11 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_revers_three(t_info *b)
{
	if (b->size < 3)
		return ;
	if (t_d(b) < tp_d(b) && t_d(b) < tpp_d(b))
	{
		sb(b, TRUE);
		rb(b, TRUE);
		sb(b, TRUE);
		rrb(b, TRUE);
		if (t_d(b) > tp_d(b))
			sb(b, TRUE);
	}
	else if (tp_d(b) < t_d(b) && tp_d(b) < tpp_d(b))
	{
		rb(b, TRUE);
		sb(b, TRUE);
		rrb(b, TRUE);
		if (t_d(b) < tp_d(b))
			sb(b, TRUE);
	}
	else
	{
		if (t_d(b) < tp_d(b))
			sb(b, TRUE);
	}
}

void	sort_revers_two(t_info *stack)
{
	if (stack->tail->data < stack->tail->prev->data)
		sb(stack, TRUE);
}

void	sort_three(t_info *a)
{
	if (a->size < 3)
		return ;
	if (t_d(a) > tp_d(a) && t_d(a) > tpp_d(a))
	{
		sa(a, TRUE);
		ra(a, TRUE);
		sa(a, TRUE);
		rra(a, TRUE);
		if (t_d(a) > tp_d(a))
			sa(a, TRUE);
	}
	else if (tp_d(a) > t_d(a) && tp_d(a) > tpp_d(a))
	{
		ra(a, TRUE);
		sa(a, TRUE);
		rra(a, TRUE);
		if (t_d(a) > tp_d(a))
			sa(a, TRUE);
	}
	else
	{
		if (t_d(a) > tp_d(a))
			sa(a, TRUE);
	}
}

int	sort_two(t_info *stack)
{
	if (stack->tail->data > stack->tail->prev->data)
	{
		if (stack->name == 'a')
			sa(stack, TRUE);
		if (stack->name == 'b')
			sb(stack, TRUE);
	}
	return (0);
}
