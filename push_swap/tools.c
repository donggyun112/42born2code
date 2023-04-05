/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:04:26 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/02 22:08:53 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	__push(t_info *s1, t_info *s2, int cnt)
{
	if (s1->name == 'a')
	{
		while (cnt--)
			pa(s1, s2);
	}
	if (s1->name == 'b')
	{
		while (cnt--)
			pb(s2, s1);
	}
}

void	revers_stack(t_info *a, t_info *b, int ra, int rb)
{
	if (!a->is_end)
	{
		while (rb-- > 0)
			rrb(b, 1);
		return ;
	}
	if (ra > rb)
	{
		ra -= rb;
		while (rb-- > 0)
			rrr(a, b);
		while (ra-- > 0)
			rra(a, TRUE);
	}
	else
	{
		rb -= ra;
		while (ra-- > 0)
			rrr(a, b);
		while (rb-- > 0)
			rrb(b, TRUE);
	}
}

int	t_d(t_info *stack)
{
	return (stack->tail->data);
}

int	tp_d(t_info *stack)
{
	return (stack->tail->prev->data);
}

int	tpp_d(t_info *stack)
{
	return (stack->tail->prev->prev->data);
}
