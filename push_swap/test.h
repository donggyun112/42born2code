/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <student.42seoul.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:25:37 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/02 01:08:46 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdlib.h>

typedef struct s_list
{
	int				data;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_info
{
	int				size;
	int				is_odd;
	int				run_checker;
	int				is_end;
	char			name;
	struct s_list	*head;
	struct s_list	*tail;
}	t_info;

typedef struct s_count
{
	int	count_ra;
	int	count_rb;
	int	count_push;
	int	pivot1;
	int	pivot2;

}	t_count;

typedef struct s_check
{
	char	**split_tmp;
	char	*itoa_tmp;
	int		data;
}	t_check;

typedef struct s_merge
{
	int	left_size;
	int	right_size;
	int	*left;
	int	*right;
}	t_merge;

#endif
