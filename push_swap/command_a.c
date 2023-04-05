/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:42:56 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/02 21:47:56 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	pa(t_info *stack_a, t_info *stack_b)
{
	int	data;

	if (!stack_b->size)
		return (0);
	data = stack_b->tail->data;
	pop_back(stack_b);
	push(stack_a, data);
	if (!stack_a->run_checker)
		ft_putstr("pa\n");
	return (1);
}

void	sa(t_info *stack_a, int flag)
{
	int	data_new;
	int	data_old;

	if (!stack_a || stack_a->size < 2)
		return ;
	data_old = stack_a->tail->data;
	data_new = stack_a->tail->prev->data;
	pop_back(stack_a);
	pop_back(stack_a);
	push(stack_a, data_old);
	push(stack_a, data_new);
	if (flag == TRUE)
		ft_putstr("sa\n");
}

void	rra(t_info *stack_a, int flag)
{
	int		data;

	if (flag == TRUE)
		ft_putstr("rra\n");
	if (!stack_a || stack_a->size < 2)
		return ;
	data = stack_a->head->data;
	pop_front(stack_a);
	push(stack_a, data);
}

int	ra(t_info *stack_a, int flag)
{
	t_list	*tmp;

	if (flag == TRUE)
		ft_putstr("ra\n");
	if (!stack_a || stack_a->size < 2)
		return (1);
	tmp = stack_a->tail;
	stack_a->tail = stack_a->tail->prev;
	stack_a->tail->next = NULL;
	tmp->next = stack_a->head;
	stack_a->head->prev = tmp;
	tmp->prev = NULL;
	stack_a->head = tmp;
	return (1);
}
