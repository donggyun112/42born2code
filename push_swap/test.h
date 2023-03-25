# ifndef TEST_H
# define TEST_H

# include <stdlib.h>

typedef struct s_list
{
	int data;
	struct s_list *next;
	struct s_list *prev;
}	t_list;

typedef struct s_info
{
	int	size;
	struct s_list *head;
	struct s_list *tail;
}	t_info;

#endif

/*

// 리스트를 2등분하는 함수
void split(t_list *head, t_list **left, t_list **right)
{
    t_list *fast;
    t_list *slow;

    if (!head || !head->next)
    {
        *left = head;
        *right = NULL;
        return;
    }

    slow = head;
    fast = head->next;
    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = head;
    *right = slow->next;
    (*right)->prev = NULL;
    slow->next = NULL;
}

// 두 정렬된 리스트를 합쳐서 하나의 정렬된 리스트로 만드는 merge 함수
t_list *merge(t_list *left, t_list *right)
{
    t_list *result_head;
    t_list *result_tail;

    if (!left)
        return (right);
    if (!right)
        return (left);

    if (left->data <= right->data)
    {
        result_head = left;
        left = left->next;
    }
    else
    {
        result_head = right;
        right = right->next;
    }
    result_tail = result_head;

    while (left && right)
    {
        if (left->data <= right->data)
        {
            result_tail->next = left;
            left->prev = result_tail;
            left = left->next;
        }
        else
        {
            result_tail->next = right;
            right->prev = result_tail;
            right = right->next;
        }
        result_tail = result_tail->next;
    }

    if (left)
    {
        result_tail->next = left;
        left->prev = result_tail;
    }
    else if (right)
    {
        result_tail->next = right;
        right->prev = result_tail;
    }

    return (result_head);
}

// merge sort 함수
void merge_sort(t_list **head)
{
    t_list *current = *head;
    t_list *left;
    t_list *right;

    if (!current || !current->next)
        return;

    split(current, &left, &right);

    merge_sort(&left);
    merge_sort(&right);

    *head = merge(left, right);
}

*/

/* void	merge(t_info *left, t_info *right, int size, int flag)
{	
	int max;
	int min;
	int flag2 = 0;

	max = 0;
	min = INT_MAX;
	get_extrem(*left, size, &max, &min);
	while (size)
	{
		if (right->tail->data == min && right->tail->data < left->tail->data)
		{
			if (flag == 1)
			{
				pa(left, right);
				rra(left, TRUE);
			}
			if (flag == 2)
			{
				pb(right, left);
				rrb(left, TRUE);
			}
			size--;
		}
		else if (right->tail->data > left->tail->data)
		{
			if (flag == 1)
				pa(left, right);
			if (flag == 2)
				pb(right, left);
			size--;
		}
		else
		{
			if (flag == 1)
				rra(left, TRUE);
			if (flag == 2)
				rrb(left, TRUE);
		}
	}
}

void ft_mergesort(t_info *left, t_info *right, int size, int flag)
{
	int	mid;
	if (size < 2)
	{
		if (left->size < 2)
			return ;
		if (left->tail->data < left->tail->prev->data)
		{
			if (flag == 1)
				sa(left, TRUE);
			else if (flag == 2)
				sb(left, TRUE);
		}
		return ;
	}
	mid = size / 2;
	for (int x = 0; x < mid; x++)
	{
		if (flag == 1)
			pb(left, right);
		else if (flag == 2)
			pa(right, left);
	}
	ft_mergesort(left, right, mid, 1);
	ft_mergesort(right, left, size - mid, 2);
	merge(left, right, size, flag);
} */