/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:46:11 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/02 21:48:03 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rb(t_info *stack_b, int flag)
{
	t_list	*tmp;

	if (flag == TRUE)
		ft_putstr("rb\n");
	if (!stack_b || stack_b->size < 2)
		return (1);
	tmp = stack_b->tail;
	stack_b->tail = stack_b->tail->prev;
	stack_b->tail->next = NULL;
	tmp->next = stack_b->head;
	stack_b->head->prev = tmp;
	tmp->prev = NULL;
	stack_b->head = tmp;
	return (1);
}

void	rrb(t_info *stack_b, int flag)
{
	int		data;

	if (flag == TRUE)
		ft_putstr("rrb\n");
	if (!stack_b || stack_b->size < 2)
		return ;
	data = stack_b->head->data;
	pop_front(stack_b);
	push(stack_b, data);
}

int	pb(t_info *stack_a, t_info *stack_b)
{
	int	data;

	if (!stack_a->size)
		return (0);
	data = stack_a->tail->data;
	pop_back(stack_a);
	push(stack_b, data);
	if (!stack_a->run_checker)
		ft_putstr("pb\n");
	return (1);
}

void	sb(t_info *stack_b, int flag)
{
	int	data_new;
	int	data_old;

	if (!stack_b || stack_b->size < 2)
		return ;
	data_old = stack_b->tail->data;
	data_new = stack_b->tail->prev->data;
	pop_back(stack_b);
	pop_back(stack_b);
	push(stack_b, data_old);
	push(stack_b, data_new);
	if (flag == TRUE)
		ft_putstr("sb\n");
}
