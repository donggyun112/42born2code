/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_init_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:54:21 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/03 23:34:26 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_init(t_info *stack, int ac, char **av)
{
	int		i;
	int		j;
	t_check	t;

	i = 0;
	j = 0;
	while (++i < ac)
	{
		t.split_tmp = ft_split(av[i], ' ');
		if (!t.split_tmp || !*(t.split_tmp))
			error_exit();
		else
		{
			j = 0;
			ft_init_split_data(stack, &t);
			while (t.split_tmp[j])
			{
				free(t.split_tmp[j]);
				j++;
			}
			free(t.split_tmp);
		}
	}
	check_duble(stack);
}

void	ft_init_split_data(t_info *stack, t_check *t)
{
	int	j;

	j = 0;
	while (t->split_tmp[j])
	{
		t->data = ft_atoi(t->split_tmp[j]);
		t->itoa_tmp = ft_itoa(t->data);
		if (ft_strcmp(t->split_tmp[j], t->itoa_tmp) == -1)
		{
			free(t->itoa_tmp);
			error_exit();
		}
		free(t->itoa_tmp);
		push_front(stack, t->data);
		j++;
	}
}

void	check_duble(t_info *stack)
{
	int		*arr;
	int		i;
	t_list	*node;

	arr = (int *)malloc(sizeof(int) * stack->size);
	if (!arr)
		return ;
	i = 0;
	node = stack->head;
	while (i < stack->size)
	{
		arr[i] = node->data;
		node = node->next;
		i++;
	}
	merge_sort(arr, stack->size);
	i = 0;
	while (++i < stack->size)
		if (arr[i - 1] == arr[i])
			error_exit();
	free(arr);
}

void	is_sorted(t_info *stack)
{
	t_list	*node;
	int		t;

	if (stack->size < 1)
		return ;
	node = stack->head;
	t = 0;
	while (node->next)
	{
		if (node->data < node->next->data)
			t++;
		node = node->next;
	}
	if (!t)
	{
		if (stack->run_checker)
			ft_putstr("OK\n");
		exit(0);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (-1);
	if (*s1 == '+')
		s1++;
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (-1);
		s1++;
		s2++;
	}
	return (0);
}
