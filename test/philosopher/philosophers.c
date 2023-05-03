/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <student.42seoul.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:52:06 by dongkseo          #+#    #+#             */
/*   Updated: 2023/05/03 00:08:20 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (-1);
	if (*s1 == '+')
		s1++;
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (-1);
		s1++;
		s2++;
	}
	return (0);
}

int	nb_len(long long nb)
{
	int	length;

	length = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		length++;
	}
	return (length);
}

void	write_int(long long nb, char *arr, int *lev)
{
	if (nb > 9)
		write_int(nb / 10, arr, lev);
	arr[*lev] = (nb % 10 + '0');
	*lev += 1;
}

char	*ft_itoa(int n)
{
	long long	nb;
	int			lev;
	char		*arr;

	nb = (long long)n;
	lev = 0;
	if (nb < 0)
	{
		nb *= -1;
		lev = 1;
		arr = (char *)malloc(nb_len(nb) + 2);
		if (!arr)
			return (NULL);
		arr[0] = '-';
	}
	else
		arr = (char *)malloc(nb_len(nb) + 1);
	if (!arr)
		return (NULL);
	write_int(nb, arr, &lev);
	arr[lev] = '\0';
	return (arr);
}

int	ft_check_data(t_check *t)
{
	int	j;

	j = 0;
	while (t->split_tmp[j])
	{
		t->data = ft_atoi(t->split_tmp[j]);
		t->itoa_tmp = ft_itoa(t->data);
		if (ft_strcmp(t->split_tmp[j], t->itoa_tmp) == -1 || t->data < 0)
		{
			free(t->itoa_tmp);
			return (1);
		}
		free(t->itoa_tmp);
		j++;
	}
	return (0);
}

int	ft_check(int ac, char **av)
{
	int		i;
	int		j;
	t_check	t;

	i = 0;
	while (++i < ac)
	{
		t.split_tmp = ft_split(av[i], ' ');
		if (!t.split_tmp || !*(t.split_tmp))
			return (1);
		else
		{
			j = 0;
			if (ft_check_data(&t))
				return (1);
			while (t.split_tmp[j])
			{
				free(t.split_tmp[j]);
				j++;
			}
			free(t.split_tmp);
		}
	}
	return (0);
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

t_table	*get_info(int ac, char **av)
{
	t_table *table;

	table = (t_table *)malloc(sizeof(t_table));
	table->num_of_philo = ft_atoi(av[1]);
	table->time_of_die = ft_atoi(av[2]);
	table->time_of_eat = ft_atoi(av[3]);
	table->time_of_sleep = ft_atoi(av[4]);
	table->count = 0;
	table->name = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->num_of_philo);
	if (ac == 6)
		table->limit_of_eat = ft_atoi(av[5]);
	else
		table->limit_of_eat = -1;
	return (table);
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
		usleep(philo->table->time_of_eat * 300);
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
				philo_print(philo, "died", 0);
				for (int x = 0; x < philo->table->num_of_philo; x++)
					pthread_detach(philo[x].thread);
				return ;
			}
			if (philo[i].table->count == philo->table->num_of_philo)
			{	
				philo_print(philo, "yummy", 0);
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

int	run(int ac, char **av, int *error_code)
{
	t_table		*table;
	t_philo		*philo;
	int			i;

	if (ft_check(ac, av))
		return (1);
	table = get_info(ac, av);
	philo = init_philo(table);
	table->philo = philo;
	i = -1;
	while (++i < table->num_of_philo)
		pthread_create(&philo[i].thread, NULL, philosophers, (void *)&(philo[i]));
	monitor(philo, table->num_of_philo);
	free_all_arg(table, philo, table->num_of_philo);
	return (0);
}

int main(int ac, char **av)
{
	int	error_code;

	error_code = 0;
	if (ac == 5 || ac == 6)
	{
		if (!run(ac, av, &error_code))
			return (0);
		printf("program Error\n");
		return (error_code);
	}
	else
		printf("argument Error\n");
	return (1);
}