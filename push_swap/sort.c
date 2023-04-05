/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:09:03 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/04 01:59:35 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sort_five(t_info *a, t_info *b)
{
	int	max;
	int	flag;
	int	do_func;

	do_func = pb(a, b) + pb(a, b) + simplesort(a) + sort_two(b);
	max = a->head->data;
	if (a->head->data < b->tail->data)
		return (do_func = ft_in_bottom(a, b) + ft_in_bottom(a, b));
	while (b->size > 0)
	{
		flag = (max < b->tail->data);
		if (max < b->tail->data)
			break ;
		if (a->tail->data > b->tail->data)
			pa(a, b);
		else
			ra(a, 1);
	}
	while (a->head->data != max)
		ra(a, 1);
	if (flag == 1)
		ft_in_bottom(a, b);
	return (0);
}

int	simplesort(t_info *a)
{
	if (t_d(a) > tp_d(a) && t_d(a) > tpp_d(a))
	{
		ra(a, TRUE);
		if (t_d(a) > tp_d(a))
			sa(a, TRUE);
	}
	else if (tp_d(a) > t_d(a) && tp_d(a) > tpp_d(a))
	{
		rra(a, TRUE);
		if (t_d(a) > tp_d(a))
			sa(a, TRUE);
	}
	else
	{
		if (t_d(a) > tp_d(a))
			sa(a, TRUE);
	}
	return (0);
}

void	sort_a(t_info *a, int cnt)
{
	if (cnt == 2)
		sort_two(a);
	if (cnt == 3)
		sort_three(a);
}

void	sort_b(t_info *a, t_info *b, int cnt)
{
	if (cnt == 3)
		sort_revers_three(b);
	if (cnt == 2)
		sort_revers_two(b);
	__push(a, b, cnt);
}
