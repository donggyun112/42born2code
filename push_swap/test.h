/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:25:37 by dongkseo          #+#    #+#             */
/*   Updated: 2023/03/31 20:25:49 by dongkseo         ###   ########.fr       */
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
	int		flag_to_delete;
}	t_check;

#endif
