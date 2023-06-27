/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:11:35 by dongkseo          #+#    #+#             */
/*   Updated: 2023/06/21 20:53:56 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	get_pivot(int *p1, int *p2, t_info *a, int size)
{
	int		*arr;
	int		i;
	t_list	*node;

	node = a->tail;
	arr = (int *)malloc(sizeof(int) * size);
	if (!arr)
		return ;
	i = 0;
	while (size--)
	{
		arr[i] = node->data;
		node = node->prev;
		i++;
	}
	merge_sort(arr, i);
	// for (int x = 0; x < z; x++)
	// 	printf("%d\n", arr[x]);
	*p1 = arr[(i + 1) / 3 - 1];
	*p2 = arr[((i + 1) / 3) * 2 - 1];
	free(arr);
}

void	b_to_a(t_info *a, t_info *b, int cnt)
{
	t_count	t;

	set_count(&t);
	if (cnt <= 2)
	{
		sort_b(a, b, cnt);
		b->is_end = 1;
		return ;
	}
	get_pivot(&t.pivot2, &t.pivot1, b, cnt);
	while (cnt-- > 0)
	{
		if (b->tail->data <= t.pivot2)
			t.count_rb += rb(b, 1);
		else
		{
			t.count_push += pa(a, b);
			if (a->tail->data <= t.pivot1)
				t.count_ra += ra(a, TRUE);
		}
	}
	a_to_b(a, b, t.count_push - t.count_ra);
	revers_stack(a, b, t.count_ra, t.count_rb);
	a_to_b(a, b, t.count_ra);
	b_to_a(a, b, t.count_rb);
}

void	a_to_b(t_info *a, t_info *b, int cnt)
{
	t_count	t;

	set_count(&t);
	if (cnt <= 3)
	{
		sort_a(a, cnt);
		a->is_end = 1;
		return ;
	}
	get_pivot(&t.pivot2, &t.pivot1, a, cnt);
	// printf("pivot1 : %d \n pivoit2 : %d\n", t.pivot1, t.pivot2);
	while (cnt-- > 0)
	{
		if (a->tail->data > t.pivot1)
			t.count_ra += ra(a, 1);
		else
		{
			t.count_push += pb(a, b);
			if (b->tail->data > t.pivot2)
				t.count_rb += rb(b, TRUE);
		}
	}
	revers_stack(a, b, t.count_ra, t.count_rb);
	a_to_b(a, b, t.count_ra);
	b_to_a(a, b, t.count_push - t.count_rb);
	b_to_a(a, b, t.count_rb);
}
