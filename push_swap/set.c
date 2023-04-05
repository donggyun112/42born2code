/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:58:09 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/02 21:58:43 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_list(t_info **node, char name)
{
	*node = (t_info *)malloc(sizeof(t_info));
	if (!*node)
		return ;
	(*node)->head = NULL;
	(*node)->tail = NULL;
	(*node)->size = 0;
	(*node)->name = name;
}

void	set_count(t_count *t)
{
	t->count_push = 0;
	t->count_ra = 0;
	t->count_rb = 0;
}
