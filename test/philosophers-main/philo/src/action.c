/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <student.42seoul.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:15:24 by seongmpa          #+#    #+#             */
/*   Updated: 2023/05/02 01:00:52 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	set_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->left]);
	philo_print(philo, "has taken a fork", 1);
	if (philo->table->num != 1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->right]);
		philo_print(philo, "has taken a fork", 1);
	}
}

static int	do_eat(t_philo *philo)
{
	philo_print(philo, "is eating", 1);
	pthread_mutex_lock(&philo->table->table_lock);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->table->table_lock);
	
	philo_pass_time(philo->table->time_to_eat);
	
	pthread_mutex_unlock(&philo->table->forks[philo->right]);
	pthread_mutex_unlock(&philo->table->forks[philo->left]);
	
	pthread_mutex_lock(&philo->table->table_lock);
	philo->must_eat_time--;
	if (philo->must_eat_time == 0)
	{
		philo->table->count++;
		pthread_mutex_unlock(&philo->table->table_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->table_lock);
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

void	*philosophers(void *param)
{
	t_philo		*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 1)
		usleep(philo->table->time_to_eat * 300);
	while (1)
	{
		set_fork(philo);
		if (philo->table->num == 1)
			break ;
		if (do_eat(philo) == 1)
			break ;
		do_sleep(philo);
		do_think(philo);
	}
	return ((void *)0);
}
