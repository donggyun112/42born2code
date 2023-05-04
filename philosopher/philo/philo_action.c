/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:44:56 by dongkseo          #+#    #+#             */
/*   Updated: 2023/05/05 01:51:26 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_pickup_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->table->fork[philo->left]);
		philo_print(philo, "has taken a fork", 0);
		pthread_mutex_lock(&philo->table->fork[philo->right]);
		philo_print(philo, "has taken a fork", 0);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->fork[philo->right]);
		philo_print(philo, "has taken a fork", 0);
		pthread_mutex_lock(&philo->table->fork[philo->left]);
		philo_print(philo, "has taken a fork", 0);
	}
}

int	philo_eating(t_philo *philo)
{
	philo_print(philo, "is eating", 0);
	pthread_mutex_lock(&philo->table->safe);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->table->safe);
	wait_(philo->table->time_of_eat);
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&philo->table->fork[philo->right]);
		pthread_mutex_unlock(&philo->table->fork[philo->left]);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->table->fork[philo->left]);
		pthread_mutex_unlock(&philo->table->fork[philo->right]);
	}
	pthread_mutex_lock(&philo->table->safe);
	philo->must_eat--;
	if (philo->must_eat == 0)
	{
		philo->table->count++;
		pthread_mutex_unlock(&philo->table->safe);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->safe);
	return (0);
}

void	philo_sleeping(t_philo *philo)
{
	philo_print(philo, "is sleeping", 0);
	wait_(philo->table->time_of_sleep);
}

void	philo_thinking(t_philo *philo)
{
	philo_print(philo, "is thinking", 0);
}

void	philo_print(t_philo *ph, char *msg, int flag)
{
	long long	now;

	usleep(300);
	if (flag == 1)
		now = get_time() - 2;
	else
		now = get_time();
	pthread_mutex_lock(&ph->table->print_mutex);
	printf("%lld %d %s\n", (now - ph->table->start_time), ph->id + 1, msg);
	if (flag == 0)
		pthread_mutex_unlock(&ph->table->print_mutex);
}
