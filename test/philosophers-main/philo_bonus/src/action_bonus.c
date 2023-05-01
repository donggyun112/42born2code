/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongmpa <seongmpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:14:21 by seongmpa          #+#    #+#             */
/*   Updated: 2023/03/30 15:58:26 by seongmpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	set_fork(t_philo *philo)
{
	sem_wait(philo->table->forks);
	philo_print(philo, "has taken a fork", 1);
	if (philo->table->num != 1)
	{
		sem_wait(philo->table->forks);
		philo_print(philo, "has taken a fork", 1);
	}
}

static int	do_eat(t_philo *philo)
{
	philo_print(philo, "is eating", 1);
	philo->last_eat_time = get_time();
	philo_pass_time(philo->table->time_to_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
	philo->must_eat_time--;
	if (philo->must_eat_time == 0)
		return (1);
	return (0);
}

static void	do_sleep(t_philo *philo)
{
	philo_print(philo, "is sleeping", 1);
	philo_pass_time(philo->table->time_to_sleep);
}

static void	do_think(t_philo *philo)
{
	philo_print(philo, "is thinking", 1);
}

void	philosophers(t_philo *philo, t_table *table)
{
	pthread_t	tid;

	pthread_create(&tid, NULL, monitoring, philo);
	if (philo->id % 2 == 1)
		usleep(table->time_to_eat * 300);
	while (1)
	{
		set_fork(philo);
		if (table->num == 1)
		{
			while (1)
				;
		}
		if (do_eat(philo) == 1)
			break ;
		do_sleep(philo);
		do_think(philo);
	}
	exit(0);
}
