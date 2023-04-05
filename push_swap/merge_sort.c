/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:37:52 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/02 21:39:45 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	merge(int arr[], int left[], t_merge t, int right[])
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < t.left_size && j < t.right_size)
	{
		if (left[i] <= right[j])
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];
	}
	while (i < t.left_size)
		arr[k++] = left[i++];
	while (j < t.right_size)
		arr[k++] = right[j++];
}

void	merge_sort(int *arr, int size)
{
	const int	mid = size / 2;
	int			i;
	t_merge		t;

	if (size < 2)
		return ;
	t.left = (int *)malloc(sizeof(int) * mid);
	if (!t.left)
		return ;
	t.right = (int *)malloc(sizeof(int) * size - mid);
	if (!t.right)
		return ;
	i = -1;
	while (++i < mid)
		t.left[i] = arr[i];
	i = mid - 1;
	while (++i < size)
		t.right[i - mid] = arr[i];
	merge_sort (t.left, mid);
	merge_sort (t.right, size - mid);
	t.left_size = mid;
	t.right_size = size - mid;
	merge (arr, t.left, t, t.right);
	free(t.left);
	free(t.right);
}
