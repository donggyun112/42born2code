/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:15:14 by seongmpa          #+#    #+#             */
/*   Updated: 2023/05/01 23:21:33 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_print(t_philo *philo, char *str, int flag)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%lld %d %s\n", get_time() - philo->start_time, philo->id, str);
	if (flag == 1)
		pthread_mutex_unlock(&philo->table->print);
}

void	withdraw_all(t_table *table, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		pthread_detach(table->philo[i].tid);
}

void	check_finish(t_table *table, int num)
{
	int	i;

	while (1)
	{
		usleep(100);
		i = -1;
		while (++i < num)
		{
			pthread_mutex_lock(&table->table_lock);
			if (get_time() - table->philo[i].last_eat_time > table->time_to_die)
			{
				philo_print(&table->philo[i], "died", 0);
				withdraw_all(table, num);
				return ;
			}
			if (table->count == table->num)
			{
				withdraw_all(table, num);
				printf("Every philosophers have a happy meal~\n");
				return ;
			}
			pthread_mutex_unlock(&table->table_lock);
		}
	}
}

void	free_all_arg(t_table *table, t_philo *philo, int num, char **str)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->table_lock);
	while (++i < num)
		pthread_mutex_destroy(&table->forks[i]);
	free(table->forks);
	free(table);
	free(philo);
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	main(int argc, char **argv)
{
	char	**str;
	t_table	*table;
	t_philo	*philo;
	int		philo_num;
	int		i;

	(void)argc;
	str = make_str(argv);
	if (check_str(str) == -1)
		return (print_error("Invalid arguments.", 1));
	philo_num = ft_atoi(str[1]);
	table = init_table(str, philo_num);
	philo = init_philo(philo_num, table);
	table->philo = philo;
	i = -1;
	while (++i < philo_num)
		pthread_create(&philo[i].tid, NULL, philosophers, (void *)&philo[i]);
	check_finish(table, philo_num);
	free_all_arg(table, philo, philo_num, str);
	return (0);
}
