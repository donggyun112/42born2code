/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:52:06 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/28 23:02:25 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

float timediff(struct timeval start, struct timeval end)
{
	return (end.tv_sec - start.tv_sec);
}

long long	get_time(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	if (time.tv_usec > 2)
		ms = (time.tv_sec * 1000) + (time.tv_usec * 1e-3);
	else
		ms = (time.tv_sec * 1000);
	return (ms);
}

void	philo_print(t_philo *ph, char *msg)
{
	long long now;

	now = get_time();
	pthread_mutex_lock(&ph->table->print_mutex);
	//if (!ph->table->finish)
		printf("%lld %d %s\n", now - ph->table->start_time , ph->id + 1, msg);
	pthread_mutex_unlock(&ph->table->print_mutex);
}

void	wait_(int time)
{
	long long	t1;

	t1 = get_time();
	while (get_time() - t1 < time)
		usleep(500);
}

int	get_info(int ac, char **av, t_table *p)
{
	p->num_of_philo = ft_atoi(av[1]);
	p->time_of_die = ft_atoi(av[2]);
	p->time_of_eat = ft_atoi(av[3]);
	p->time_of_sleep = ft_atoi(av[4]);
	if (ac == 6)
		p->limit_of_eat = ft_atoi(av[5]);
	return (0);
}

void	init_philo(t_table *table, t_philo *ph)
{
	int	i;

	table->name = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->num_of_philo);
	memset(table->name, 0, sizeof(pthread_mutex_t) * table->num_of_philo);
	if (!table->name)
		return ;
	table->start_time = get_time();
	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_mutex_init(&table->name[i], NULL);
		ph[i].id = i;
		ph[i].num_eaten = 0;
		ph[i].table = table;
		ph[i].last_eat = get_time();
		i++;
	}
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->finish_mutex, NULL);
	pthread_mutex_init(&table->time_mutex, NULL);
}

void	philo_pickup_fork(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->table->num_of_philo;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->name[right]);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->name[left]);
		philo_print(philo, "has taken a fork");
	}
	else if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->table->name[left]);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->name[right]);
		philo_print(philo, "has taken a fork");	
	}
}

pthread_mutex_t time_mutex;

void	philo_eating(t_philo *philo)
{
	int	left;
	int	right;

	if (philo)
	pthread_mutex_lock(&philo->table->time_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->table->time_mutex);
	philo_print(philo, "is eating");
	philo->num_eaten++;
	left = philo->id;
	right = (philo->id + 1) % philo->table->num_of_philo;
	wait_(philo->table->time_of_eat);
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&philo->table->name[left]);
		pthread_mutex_unlock(&philo->table->name[right]);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->table->name[right]);
		pthread_mutex_unlock(&philo->table->name[left]);
	}
}

void	philo_sleeping(t_philo *philo)
{
	philo_print(philo, "is sleeping");
	wait_(philo->table->time_of_sleep);
}

void	philo_thinking(t_philo *philo)
{
	philo_print(philo, "is thinking");
}

void	*philosophers(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->table->finish_mutex);
		if (philo->table->finish)
		{
			pthread_mutex_unlock(&philo->table->finish_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->finish_mutex);
		if (philo->id % 2 == 0)
			wait_(1);
		philo_pickup_fork(philo);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (NULL);
}

void	*monitor(void *data)
{
	int i = 0;
	t_philo *philo;
	long long	now;

	philo = (t_philo *)data;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&philo->table->finish_mutex);
		if (philo->table->finish)
		{
			pthread_mutex_unlock(&philo->table->finish_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->table->finish_mutex);
		while (i < philo->table->num_of_philo)
		{
			now = get_time();
			pthread_mutex_lock(&philo[0].table->time_mutex);
			if (now - philo[i].last_eat >= philo->table->time_of_die)
			{
				pthread_mutex_lock(&philo->table->finish_mutex);
				philo_print(&philo[i], "died");
				philo->table->finish = 1;
				pthread_mutex_unlock(&philo->table->finish_mutex);
				break ;
			}
			pthread_mutex_unlock(&philo[0].table->time_mutex);
			i++;
		}
	}
	return (NULL);
}

int	run(int ac, char **av)
{
	t_table		data;
	t_philo		*ph;
	pthread_t monitoring;
	int			i;

	if (!get_info(ac, av, &data))
	{
		ph = (t_philo *)malloc(sizeof(t_philo) * data.num_of_philo);
		if (!ph)
			return (1);
		init_philo(&data, ph);
		data.finish = 0;
		i = 0;
		pthread_create(&monitoring, NULL, monitor, ph);
		while (i < data.num_of_philo)
		{
			pthread_create(&ph[i].thread, NULL, philosophers, &(ph[i]));
			pthread_detach(ph[i].thread);
			i++;
		}
		pthread_join(monitoring, NULL);
		return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!run(ac, av))
			return (0);
	}
	return (1);
}