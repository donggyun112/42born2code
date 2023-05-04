/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:52:06 by dongkseo          #+#    #+#             */
/*   Updated: 2023/05/04 20:05:59 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitor(t_table *table, t_philo *philo, int num)
{
	int	i;

	while (1)
	{
		i = 0;
		usleep(100);
		while (i < num)
		{
			pthread_mutex_lock(&table->safe);
			if (get_time() - philo[i].last_eat > philo->table->time_of_die)
			{
				philo_print(philo, "died", 1);
				clear_thread(philo, num);
				return ;
			}
			if (philo[i].table->count == num)
			{	
				philo_print(philo, "yummy", 1);
				clear_thread(philo, num);
				return ;
			}
			pthread_mutex_unlock(&table->safe);
			i++;
		}
	}
}
