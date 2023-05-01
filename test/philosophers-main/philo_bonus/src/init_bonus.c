/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongmpa <seongmpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:52:36 by seongmpa          #+#    #+#             */
/*   Updated: 2023/03/30 15:56:54 by seongmpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_table	*init_table_arg(char **argv, int num)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	table->num = num;
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->must_eat_time = ft_atoi(argv[5]);
	else
		table->must_eat_time = -1;
	return (table);
}

t_table	*init_table(char **argv, int num)
{
	t_table	*table;

	table = init_table_arg(argv, num);
	if (!table)
		return (NULL);
	sem_unlink("print");
	sem_unlink("table_lock");
	sem_unlink("forks");
	table->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	table->table_lock = sem_open("table_lock", O_CREAT | O_EXCL, 0644, 1);
	table->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, num);
	if (table->print == SEM_FAILED || table->table_lock == SEM_FAILED \
		|| table->forks == SEM_FAILED)
		return (NULL);
	return (table);
}

t_philo	*init_philo(int num, t_table *table, char **argv)
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
		if (argv[5])
			philo[i].must_eat_time = ft_atoi(argv[5]);
		else
			philo[i].must_eat_time = -1;
		philo[i].left = i;
		philo[i].right = (num - 1 + i) % num;
		philo[i].last_eat_time = get_time();
		philo[i].start_time = get_time();
	}
	return (philo);
}
