#include "test.h"
#include <unistd.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

int	ft_returnmax(int sign)
{
	if (sign == 1)
		return (INT_MAX);
	else
		return (INT_MIN);
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
		if (sum > INT_MAX / 10)
			return (ft_returnmax(sign));
		if (sum == INT_MAX / 10 && *str - '0' > INT_MAX % 10)
			return (ft_returnmax(sign));
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

void	push(t_info *stack_A, int data)
{
	t_list *tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	tmp->data = data;
	if (stack_A->head == NULL)
	{
		stack_A->head = tmp;
		stack_A->tail = tmp;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	else
	{
		stack_A->tail->next = tmp;
		tmp->prev = stack_A->tail;
		tmp->next = NULL;
		stack_A->tail = tmp;
	}
	stack_A->size++;
}

void	push_front(t_info *node, int data)
{
	t_list *tmp;
	
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
		tmp->data = 0;
		free(tmp);
		tmp = NULL;
		stack->tail->next = NULL;
	}
	stack->size--;
}

void	pop_front(t_info *stack)
{
	t_list *tmp;

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

int	top(t_info *stack)
{
	return (stack->head->data);
}

int bottom(t_info *stack)
{
	return (stack->tail->data);
}
#include <stdio.h>


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

int ft_check_val(char *str)
{
	while (*str)
	{
		if (!((*str >= '0' && *str <= '9') || *str == 32))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

void	ft_init(t_info *stack, int ac, char **av)
{
	int	i;
	int	data;

	i = 0;
	while (++i < ac)
	{
		if (ft_check_val(av[i]) == FALSE)
		{
			ft_lstclear(stack);
			free(stack);
			stack = NULL;
			//에러처리
			break ;
		}
		data = ft_atoi(av[i]);
		push(stack, data);
	}
}

void	set_list(t_info **node)
{
	*node = (t_info *)malloc(sizeof(t_info));
	(*node)->head = NULL;
	(*node)->tail = NULL;
	(*node)->size = 0;
}

void	rra(t_info *stack_A, int flag)
{
	t_list	*tmp;

	if (!stack_A || stack_A->size < 2)
		return ;
	tmp = stack_A->tail;
	stack_A->tail = stack_A->tail->prev;
	stack_A->tail->next = NULL;
	tmp->next = stack_A->head;
	stack_A->head->prev = tmp;
	tmp->prev = NULL;
	stack_A->head = tmp;
	if (flag == TRUE)
		ft_putstr("rra\n");
}

void	rrb(t_info *stack_B, int flag)
{
	t_list	*tmp;

	if (!stack_B || stack_B->size < 2)
		return ;
	tmp = stack_B->tail;
	stack_B->tail = stack_B->tail->prev;
	stack_B->tail->next = NULL;
	tmp->next = stack_B->head;
	stack_B->head->prev = tmp;
	tmp->prev = NULL;
	stack_B->head = tmp;
	if (flag == TRUE)
		ft_putstr("rrb\n");
}

void	ra(t_info *stack_A, int flag)
{
	t_list	*tmp;
	int		data;

	if (!stack_A || stack_A->size < 2)
		return ;
	/* tmp = stack_A->head;
	stack_A->head = stack_A->head->next;
	stack_A->head->prev = NULL;
	stack_A->tail->next = tmp;
	tmp->prev = stack_A->tail;
	tmp->next = NULL;
	stack_A->tail = tmp; */
	data = stack_A->head->data;
	pop_front(stack_A);
	push(stack_A, data);
	if (flag == TRUE)
		ft_putstr("ra\n");
}

void	rb(t_info *stack_B, int flag)
{
	t_list	*tmp;
	int		data;

	if (!stack_B || stack_B->size < 2)
		return ;
	/* tmp = stack_B->head;
	stack_B->head = stack_B->head->next;
	stack_B->head->prev = NULL;
	stack_B->tail->next = tmp;
	tmp->next = NULL;
	tmp->prev = stack_B->tail;
	stack_B->tail = tmp; */
	data = stack_B->head->data;
	pop_front(stack_B);
	push(stack_B, data);
	if (flag == TRUE)
		ft_putstr("rb\n");
}

void	rr(t_info *stack_A, t_info *stack_B)
{
	if (!stack_A->head || !stack_B->head)
		return ;
	if (!stack_A->head->next || !stack_B->head->next)
		return ;
	ra(stack_A, FALSE);
	rb(stack_B, FALSE);
	ft_putstr("rr\n");
}

void	sa(t_info *stack_A, int flag)
{
	int	data_new;
	int	data_old;
	if (!stack_A || stack_A->size < 2)
		return ;
	data_old = stack_A->tail->data;
	data_new = stack_A->tail->prev->data;
	pop_back(stack_A);
	pop_back(stack_A);
	push(stack_A, data_old);
	push(stack_A, data_new);
	if (flag == TRUE)
		ft_putstr("sa\n");
}

void	sb(t_info *stack_B, int flag)
{
	t_list	*tmp;
	int	data_new;
	int	data_old;

	if (!stack_B || stack_B->size < 2)
		return ;
	data_old = stack_B->tail->data;
	data_new = stack_B->tail->prev->data;
	pop_back(stack_B);
	pop_back(stack_B);
	push(stack_B, data_old);
	push(stack_B, data_new);
	if (flag == TRUE)
		ft_putstr("sb\n");
}

void	pa(t_info *stack_A, t_info *stack_B)
{
	int	data;

	if (!stack_A || !stack_B || !stack_B->head || !stack_B->size)
		return ;
	data = stack_B->tail->data;
	pop_back(stack_B);
	push(stack_A, data);
	ft_putstr("pa\n");
}

void	pb(t_info *stack_A, t_info *stack_B)
{
	int	data;

	if (!stack_A || !stack_B || !stack_A->head || !stack_A->size)
		return ;
	data = stack_A->tail->data;
	pop_back(stack_A);
	push(stack_B, data);
	ft_putstr("pb\n");
}

void	ss(t_info *stack_A, t_info *stack_B)
{
	if (!stack_A || stack_A->size < 2)
		return ;
	if (!stack_B || stack_B->size < 2)
		return ;
	sa(stack_A, FALSE);
	sb(stack_B, FALSE);
	ft_putstr("ss\n");
}

void	rrr(t_info *stack_A, t_info *stack_B)
{
	if (!stack_A || stack_A->size < 2)
		return ;
	if (!stack_B || stack_B->size < 2)
		return ;
	rra(stack_A, FALSE);
	rrb(stack_B, FALSE);
	ft_putstr("rrr\n");
}

void merge(int arr[], int left[], int left_size, int right[], int right_size) 
{
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    while (i < left_size) {
        arr[k++] = left[i++];
    }

    while (j < right_size) {
        arr[k++] = right[j++];
    }
}

void merge_sort(int arr[], int size) 
{
    if (size < 2) {
        return;
    }

    int mid = size / 2;
    int left[mid];
    int right[size - mid];

    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }

    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }

    merge_sort(left, mid);
    merge_sort(right, size - mid);
    merge(arr, left, mid, right, size - mid);
}

void	get_pivot(int *p1, int *p2, t_info a)
{
	int	*arr;
	int	i;

	if (a.size == 1 || a.size == 2)
	{
		*p1 = a.head->data;
		*p1 = a.tail->data;
		return ;
	}
	arr = (int *)malloc(sizeof(int) * a.size);
	if (!arr)
		return ;
	i = 0;
	while (a.head)
	{
		arr[i] = a.head->data;
		a.head = a.head->next;
		i++;
	}
	merge_sort(arr, a.size);
	*p1 = arr[(a.size / 3) - 1];
	*p2 = arr[((a.size / 3) * 2) - 1];
}

void a_to_b(t_info *a, t_info *b, int cnt)
{
    int pivot1, pivot2;

    if (cnt < 5)
	{
		// 정렬하드코딩
        return;
	}
    else
    {
		get_pivot(&pivot1, &pivot2, *a);
        for (int i = 0; i < cnt; i++)
        {
            if (a->tail->data > pivot2)
                ra(a, TRUE);
            else if (a->tail->data >= pivot1 && a->tail->data <= pivot2)
            {
                pb(a, b);
            }
            else
			{
                pb(a, b);
				rrb(b, TRUE);
			}
        }
    }
	a_to_b(a, b, a->size);
	int z = 3;
}

int main(int ac, char **av)
{
	t_info *stack_A;
	t_info *stack_B;

	if (ac < 2)
		return (-1);
	set_list(&stack_A);
	set_list(&stack_B);
	ft_init(stack_A, ac, av);
	a_to_b(stack_A, stack_B, stack_A->size);
	int z = 3;
	return (0);
}
