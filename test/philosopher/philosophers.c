/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:52:06 by dongkseo          #+#    #+#             */
/*   Updated: 2023/05/01 23:43:31 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	if (time.tv_usec > 2)
		ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	else
		ms = (time.tv_sec * 1000);
	return (ms);
}

void	philo_print(t_philo *ph, char *msg, int flag)
{
	long long	now;

	now = get_time();
	pthread_mutex_lock(&ph->table->print_mutex);
	printf("%lld %d %s\n", now - ph->table->start_time , ph->id + 1, msg);
	if (flag == 1)
		pthread_mutex_unlock(&ph->table->print_mutex);
}

void	wait_(int time)
{
	long long	t1;

	t1 = get_time() + time;
	while (get_time() < t1)
		usleep(100);
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
	if (!table->name)
		return ;
	table->start_time = get_time();
	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_mutex_init(&table->name[i], NULL);
		ph[i].id = i;
		ph[i].table = table;
		ph[i].left = i;
		ph[i].right = (i + 1) % table->num_of_philo;
		ph[i].must_eat = table->limit_of_eat;
		ph[i].last_eat = get_time();
		i++;
	}
	pthread_mutex_init(&table->safe, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
}

void	philo_pickup_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->name[philo->left]);
	philo_print(philo, "has taken a fork", 1);
	if (philo->table->num_of_philo != 1)
	{
		pthread_mutex_lock(&philo->table->name[philo->right]);
		philo_print(philo, "has taken a fork", 1);
	}
}

int	philo_eating(t_philo *philo)
{
	philo_print(philo, "is eating", 1);
	pthread_mutex_lock(&philo->table->safe);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->table->safe);
	wait_(philo->table->time_of_eat);
	pthread_mutex_unlock(&philo->table->name[philo->right]);
	pthread_mutex_unlock(&philo->table->name[philo->left]);
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
	philo_print(philo, "is sleeping", 1);
	wait_(philo->table->time_of_sleep);
}

void	philo_thinking(t_philo *philo)
{
	philo_print(philo, "thinking", 1);
}

void	*philosophers(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 1)
		usleep(philo->table->limit_of_eat * 300);
	while (1)
	{
		philo_pickup_fork(philo);
		if (philo->table->num_of_philo == 1)
			break ;
		if (philo_eating(philo) == 1)
			break ;
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (NULL);
}

void	monitor(t_philo *philo, int num)
{
	int	i;

	while (1)
	{
		usleep(100);
		i = 0;
		while (i < num)
		{
			pthread_mutex_lock(&philo->table->safe);
			if (get_time() - philo[i].last_eat > philo->table->time_of_die)
			{
				philo_print(philo, "2", 0);
				for (int x = 0; x < philo->table->num_of_philo; x++)
					pthread_detach(philo[x].thread);
				return ;
			}
			if (philo[i].table->count == philo->table->num_of_philo)
			{	
				philo_print(philo, "1", 0);
				for (int x = 0; x < philo->table->num_of_philo; x++)
					pthread_detach(philo[x].thread);
				return ;
			}
			pthread_mutex_unlock(&philo->table->safe);
			i++;
		}
		
	}
}

void	free_all_arg(t_table *table, t_philo *philo, int num)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->safe);
	while (++i < num)
		pthread_mutex_destroy(&table->name[i]);
	free(table->name);
	free(philo);
	i = -1;
	while (++i < 10);
}

int	run(int ac, char **av)
{
	t_table		data;
	t_philo		*ph;
	int			i;

	if (!get_info(ac, av, &data))
	{
		ph = (t_philo *)malloc(sizeof(t_philo) * data.num_of_philo);
		if (!ph)
			return (1);
		init_philo(&data, ph);
		data.philo = ph;
		i = -1;
		while (++i < data.num_of_philo)
			pthread_create(&ph[i].thread, NULL, philosophers, (void *)&(ph[i]));
		monitor(ph, data.num_of_philo);
		free_all_arg(&data, ph, data.num_of_philo);
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