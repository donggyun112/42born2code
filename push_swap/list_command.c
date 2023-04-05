/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:52:40 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/02 21:53:10 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_front(t_info *node, int data)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		exit(-1);
	tmp->data = data;
	tmp->prev = NULL;
	if (node->head == NULL)
	{
		tmp->next = NULL;
		node->head = tmp;
		node->tail = tmp;
	}
	else
	{
		tmp->next = node->head;
		node->head->prev = tmp;
		node->head = tmp;
	}
	node->size++;
}

void	push(t_info *stack_a, int data)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		exit(-1);
	tmp->data = data;
	if (stack_a->head == NULL)
	{
		stack_a->head = tmp;
		stack_a->tail = tmp;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	else
	{
		stack_a->tail->next = tmp;
		tmp->prev = stack_a->tail;
		tmp->next = NULL;
		stack_a->tail = tmp;
	}
	stack_a->size++;
}

void	pop_back(t_info *stack)
{
	t_list	*tmp;

	if (stack->size == 1)
	{
		stack->head->data = 0;
		free(stack->head);
		stack->head = NULL;
		stack->tail = NULL;
	}
	else
	{
		tmp = stack->tail;
		stack->tail = stack->tail->prev;
		tmp->prev = NULL;
		tmp->data = 0;
		free(tmp);
		stack->tail->next = NULL;
	}
	stack->size--;
}

void	pop_front(t_info *stack)
{
	t_list	*tmp;

	if (stack->size == 1)
	{
		stack->head->data = 0;
		free(stack->head);
		stack->head = NULL;
		stack->tail = NULL;
	}
	else
	{
		tmp = stack->head;
		stack->head = stack->head->next;
		tmp->data = 0;
		free(tmp);
		tmp = NULL;
		stack->head->prev = NULL;
	}
	stack->size--;
}
