/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <student.42seoul.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:52:06 by dongkseo          #+#    #+#             */
/*   Updated: 2023/05/03 12:46:46 by dongkseo         ###   ########.fr       */
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

void	philo_print(t_philo *ph, char *msg, int flag)
{
	long long	now;

	now = get_time();
	pthread_mutex_lock(&ph->table->print_mutex);
	printf("%lld %d %s\n", now - ph->table->start_time , ph->id + 1, msg);
	if (flag == 0)
		pthread_mutex_unlock(&ph->table->print_mutex);
}

void	wait_(int time)
{
	long long	t1;

	t1 = get_time();
	while (get_time() - t1 < time)
		usleep(500);
}

t_table	*get_info(int ac, char **av)
{
	t_table *table;

	table = (t_table *)malloc(sizeof(t_table));
	table->num_of_philo = ft_atoi(av[1]);
	table->time_of_die = ft_atoi(av[2]);
	table->time_of_eat = ft_atoi(av[3]);
	table->time_of_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->limit_of_eat = ft_atoi(av[5]);
	else
		table->limit_of_eat = -1;
	table->name = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->num_of_philo);
	if (!table->name)
		return (NULL);
	return (table);
}

void	philo_pickup_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->table->name[philo->left]);
		philo_print(philo, "has taken a fork", 0);
		pthread_mutex_lock(&philo->table->name[philo->right]);
		philo_print(philo, "has taken a fork", 0);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->name[philo->right]);
		philo_print(philo, "has taken a fork", 0);
		pthread_mutex_lock(&philo->table->name[philo->left]);
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
		pthread_mutex_unlock(&philo->table->name[philo->left]);
		pthread_mutex_unlock(&philo->table->name[philo->right]);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->table->name[philo->right]);
		pthread_mutex_unlock(&philo->table->name[philo->left]);
	}
	
	pthread_mutex_lock(&philo->table->safe);
	philo->num_eaten++;
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

void	*philosophers(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 1)
		wait_(philo->table->limit_of_eat);
	while (1)
	{
		if (philo->id % 2 == 1)
			wait_(1);
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

void	monitor(t_table *table, t_philo *philo, int num)
{
	int i = 0;
	long long	now;

	while (1)
	{
		i = 0;
		usleep(100);
		while (i < philo->table->num_of_philo)
		{
			now = get_time();
			pthread_mutex_lock(&table->safe);
			if (get_time() - philo[i].last_eat > philo->table->time_of_die)
			{
				philo_print(philo, "died", 1);
				for (int x = 0; x < philo->table->num_of_philo; x++)
					pthread_detach(philo[x].thread);
				return ;
			}
			if (philo[i].table->count == philo->table->num_of_philo)
			{	
				philo_print(philo, "all eat", 1);
				for (int x = 0; x < philo->table->num_of_philo; x++)
					pthread_detach(philo[x].thread);
				return ;
			}
			pthread_mutex_unlock(&table->safe);
			i++;
		}
	}
}

t_philo	*init_philo(t_table *table)
{
	int	i;
	t_philo *ph;

	table->start_time = get_time();
	ph = (t_philo *)malloc(sizeof(t_philo) * table->num_of_philo);
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
	return (ph);
}

int	run(int ac, char **av)
{
	t_table		*table;
	t_philo		*philo;
	pthread_t 	monitoring;
	int			i;

	table =  get_info(ac, av);
	philo = init_philo(table);
	table->finish = 0;
	table->finish_eat = 0;
	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, philosophers, &(philo[i]));
		i++;
	}
	monitor(table, philo, table->num_of_philo);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->safe);
	return (0);
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