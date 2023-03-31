#include "test.h"
#include "ft_split.c"
#include "ft_itoa.c"
#include <unistd.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

void merge(int arr[], int left[], int left_size, int right[], int right_size) 
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < left_size && j < right_size)
	{
		if (left[i] <= right[j])
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];
	}
	while (i < left_size)
		arr[k++] = left[i++];
	while (j < right_size)
		arr[k++] = right[j++];
}

void	merge_sort(int *arr, int size)
{
	const int	mid = size / 2;
	int			*left;
	int			*right;
	int			i;

	if (size < 2)
		return ;
	left = (int *)malloc(sizeof(int) * mid);
	right = (int *)malloc(sizeof(int) * size - mid);
	i = -1;
	while (++i < mid)
		left[i] = arr[i];
	i = mid - 1;
	while (++i < size)
		right[i - mid] = arr[i];
	merge_sort (left, mid);
	merge_sort (right, size - mid);
	merge (arr, left, mid, right, size - mid);
	free(left);
	free(right);
}

int	ft_atoi(const char *str)
{
	int	sum;
	int	sign;

	sum = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - '0');
		str++;
	}
	return (sum * sign);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	push(t_info *stack_a, int data)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
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

void	push_front(t_info *node, int data)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
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

void	ft_lstclear(t_info *lst)
{
	t_list	*node;

	if (!lst)
		return ;
	lst->tail = NULL;
	while (lst->head)
	{
		node = (lst)->head->next;
		(lst)->head->data = 0;
		free(lst->head);
		lst->size = 0;
		lst->head = node;
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

void	error_exit()
{
	write(2, "Error\n", 6);
	exit(-1);
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
		if (!t.split_tmp)
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

void	set_list(t_info **node, char name)
{
	*node = (t_info *)malloc(sizeof(t_info));
	(*node)->head = NULL;
	(*node)->tail = NULL;
	(*node)->size = 0;
	(*node)->name = name;
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

int	rotation(t_info *stack)
{
	if (stack->name == 'a')
		return (ra(stack, TRUE));
	if (stack->name == 'b')
		return (rb(stack, TRUE));
	return (0);
}

void	rra(t_info *stack_a, int flag)
{
	t_list	*tmp;
	int		data;
	int		rank;

	if (flag == TRUE)
		ft_putstr("rra\n");
	if (!stack_a || stack_a->size < 2)
		return ;
	data = stack_a->head->data;
	pop_front(stack_a);
	push(stack_a, data);
}

void	rrb(t_info *stack_b, int flag)
{
	t_list	*tmp;
	int		data;

	if (flag == TRUE)
		ft_putstr("rrb\n");
	if (!stack_b || stack_b->size < 2)
		return ;
	data = stack_b->head->data;
	pop_front(stack_b);
	push(stack_b, data);
}

void	rr(t_info *stack_a, t_info *stack_b)
{
	if (!stack_a->head || !stack_b->head)
		return ;
	if (!stack_a->head->next || !stack_b->head->next)
		return ;
	ra(stack_a, FALSE);
	rb(stack_b, FALSE);
	ft_putstr("rr\n");
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

void	sb(t_info *stack_b, int flag)
{
	t_list	*tmp;
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

int	pa(t_info *stack_a, t_info *stack_b)
{
	int	data;

	if (!stack_b->size)
		return (0);
	data = stack_b->tail->data;
	pop_back(stack_b);
	push(stack_a, data);
	ft_putstr("pa\n");
	return (1);
}

int	pb(t_info *stack_a, t_info *stack_b)
{
	int	data;

	if (!stack_a->size)
		return (0);
	data = stack_a->tail->data;
	pop_back(stack_a);
	push(stack_b, data);
	ft_putstr("pb\n");
	return (1);
}

void	ss(t_info *stack_a, t_info *stack_b)
{
	ft_putstr("ss\n");
	if (!stack_a || stack_a->size < 2)
		return ;
	if (!stack_b || stack_b->size < 2)
		return ;
	sa(stack_a, FALSE);
	sb(stack_b, FALSE);
}

void	rrr(t_info *stack_a, t_info *stack_b)
{
	ft_putstr("rrr\n");
	if (!stack_a || stack_a->size < 2)
		return ;
	if (!stack_b || stack_b->size < 2)
		return ;
	rra(stack_a, FALSE);
	rrb(stack_b, FALSE);
}

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
	*p1 = arr[(i + a->is_odd) / 3 - 1];
	*p2 = arr[((i + a->is_odd) / 3) * 2 - 1];
	free(arr);
}

void a_to_b(t_info *a, t_info *b, int cnt);

void	revers_stack(t_info *a, t_info *b, int ra, int rb)
{
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

void	set_count(t_count *t)
{
	t->count_push = 0;
	t->count_ra = 0;
	t->count_rb = 0;
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

void	sort_revers_three(t_info *a, t_info *b)
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

void	sort_a(t_info *a, int cnt)
{
	if (cnt == 2)
		sort_two(a);
	else
		sort_three(a);
}

void	sort_b(t_info *a, t_info *b, int cnt)
{
	if (cnt == 3)
		sort_revers_three(a, b);
	if (cnt == 2)
		sort_revers_two(b);
	__push(a, b, cnt);
}

void	b_to_a(t_info *a, t_info *b, int cnt)
{
	t_count t;

	set_count(&t);
	if (cnt <= 2)
	{
		sort_b(a, b, cnt);
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

void a_to_b(t_info *a, t_info *b, int cnt)
{
	t_count	t;

	set_count(&t);
	if (cnt <= 3)
	{
		sort_a(a, cnt);
		return ;
	}
	get_pivot(&t.pivot2, &t.pivot1, a, cnt);
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

int	ft_in_bottom(t_info *a, t_info *b)
{
	pa(a, b);
	ra(a, 1);
	return (0);
}

void	sort_five(t_info *a, t_info *b)
{
	int	max;
	int	flag;
	int	do_func;

	do_func = pb(a, b) + pb(a, b) + simplesort(a) + sort_two(b);
	max = a->head->data;
	if (a->head->data < b->tail->data)
	{
		do_func = ft_in_bottom(a, b) + ft_in_bottom(a, b);
		return ;
	}
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
}

void	all_free(t_info **a, t_info **b)
{
	ft_lstclear(*a);
	ft_lstclear(*b);
	free(*a);
	free(*b);
}

void	check_odd(t_info *stack_a, t_info *stack_b)
{
	if (stack_a->size % 2 == 1)
	{
		stack_a->is_odd = 0;
		stack_b->is_odd = 0;
	}
	else
	{
		stack_a->is_odd = 1;
		stack_b->is_odd = 1;
	}
}

int main(int ac, char **av)
{
	t_info	*stack_a;
	t_info	*stack_b;

	if (ac < 2)
		return (-1);
	set_list(&stack_a, 'a');
	ft_init(stack_a, ac, av);
	set_list(&stack_b, 'b');
	check_odd(stack_a, stack_b);
	if (stack_a->size == 3)
		simplesort(stack_a);
	else if (stack_a->size == 5)
		sort_five(stack_a, stack_b);
	else
		a_to_b(stack_a, stack_b, stack_a->size);
	exit(0);
}
