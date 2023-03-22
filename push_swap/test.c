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
		ft_putstr("rra\n");
}

void	ra(t_info *stack_A, int flag)
{
	t_list	*tmp;

	if (!stack_A || stack_A->size < 2)
		return ;
	tmp = stack_A->head;
	stack_A->head = stack_A->head->next;
	stack_A->head->prev = NULL;
	stack_A->tail->next = tmp;
	tmp->prev = stack_A->tail;
	tmp->next = NULL;
	stack_A->tail = tmp;
	if (flag == TRUE)
		ft_putstr("ra\n");
}

void	rb(t_info *stack_B, int flag)
{
	t_list	*tmp;

	if (!stack_B || stack_B->size < 2)
		return ;
	tmp = stack_B->head;
	stack_B->head = stack_B->head->next;
	stack_B->head->prev = NULL;
	stack_B->tail->next = tmp;
	tmp->next = NULL;
	tmp->prev = stack_B->tail;
	stack_B->tail = tmp;
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
	t_list	*tmp;

	if (!stack_A || stack_A->size < 2)
		return ;
	tmp = stack_A->head->next;
	stack_A->head->next = stack_A->head->next->next;
	if (stack_A->head->next)
		stack_A->head->next->prev = stack_A->head;
	stack_A->head->prev = tmp;
	tmp->prev = NULL;
	tmp->next = stack_A->head;
	stack_A->head = tmp;
	if (flag == TRUE)
		ft_putstr("sa\n");
}

void	sb(t_info *stack_B, int flag)
{
	t_list	*tmp;

	if (!stack_B || stack_B->size < 2)
		return ;
	tmp = stack_B->head->next;
	stack_B->head->next = stack_B->head->next->next;
	if (stack_B->head->next)
		stack_B->head->next->prev = stack_B->head;
	stack_B->head->prev = tmp;
	tmp->prev = NULL;
	tmp->next = stack_B->head;
	stack_B->head = tmp;
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

/* 스택 A에서 가장 작은 값을 스택 B로 이동 */
void move_min_to_b(t_info *stack_a, t_info *stack_b)
{
    int min_val = stack_a->tail->data;
    t_list *min_node = stack_a->tail;
    /* 스택 A에서 최소값 탐색 */
    if (min_val > stack_a->head->data)
    {
        min_val = stack_a->head->data;
        min_node = stack_a->head;
    }
    if (min_val > stack_a->tail->prev->data)
    {
        min_val = stack_a->tail->prev->data;
        min_node = stack_a->tail->prev;
    }
    if (min_val > stack_a->head->next->data)
    {
        min_val = stack_a->head->next->data;
        min_node = stack_a->head->next;
    }
    /* 스택 A에서 최소값을 스택 B로 이동 */
    if (min_node == stack_a->head)
        ra(stack_a, TRUE); // 최소값이 스택 A의 맨 위에 있을 때
    else if (min_node == stack_a->tail->prev)
        rra(stack_a, TRUE); // 최소값이 스택 A의 맨 아래에 있을 때
    if (min_node == stack_a->head || min_node == stack_a->head->next)
        pb(stack_a, stack_b); // 최소값이 스택 A의 위쪽에 있을 때
    else if (min_node == stack_a->tail || min_node == stack_a->tail->prev)
        pb(stack_a, stack_b); // 최소값이 스택 A의 아래쪽에 있을 때
}

/* 스택을 정렬하는 함수 */
void sort_stack(t_info *stack_a, t_info *stack_b)
{
	int i = 0;
    /* 예외 처리 */
    if (stack_a == NULL || stack_a->head == NULL || stack_a->size < 2)
        return;
    /* 스택 A의 모든 원소를 스택 B로 이동 */
    while (i < stack_a->size / 2)
        move_min_to_b(stack_a, stack_b);
    /* 스택 B에서 스택 A로 이동 */
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
	sort_stack(stack_A, stack_B);
	return (0);
}
