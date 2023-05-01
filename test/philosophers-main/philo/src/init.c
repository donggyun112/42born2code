/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongmpa <seongmpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:37:02 by seongmpa          #+#    #+#             */
/*   Updated: 2023/03/30 18:09:26 by seongmpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (*s++)
		len++;
	return (len);
}

t_philo	*init_philo(int num, t_table *table)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * num);
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < num)
	{
		philo[i].id = i;
		philo[i].eat_count = 0;
		philo[i].table = table;
		philo[i].must_eat_time = philo->table->must_eat_time;
		philo[i].left = i;
		philo[i].right = (num - 1 + i) % num;
		philo[i].last_eat_time = get_time();
		philo[i].start_time = get_time();
	}
	return (philo);
}

t_table	*init_table_arg(char **str, int num)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (!table || !table->forks)
		return (NULL);
	table->num = num;
	table->time_to_die = ft_atoi(str[2]);
	table->time_to_eat = ft_atoi(str[3]);
	table->time_to_sleep = ft_atoi(str[4]);
	table->finish = 1;
	table->count = 0;
	if (str[5])
		table->must_eat_time = ft_atoi(str[5]);
	else
		table->must_eat_time = -1;
	return (table);
}

t_table	*init_table(char **argv, int num)
{
	int		i;
	t_table	*table;

	table = init_table_arg(argv, num);
	if (pthread_mutex_init(&table->print, NULL) < 0)
	{
		free(table->forks);
		return (NULL);
	}
	if (pthread_mutex_init(&table->table_lock, NULL) < 0)
	{
		free(table->forks);
		return (NULL);
	}
	i = -1;
	while (++i < num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) < 0)
		{
			free(table->forks);
			return (NULL);
		}
	}
	return (table);
}
