/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <student.42seoul.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:52:06 by dongkseo          #+#    #+#             */
/*   Updated: 2023/05/05 03:19:41 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosophers(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 1 && philo->table->num_of_philo % 2 == 1)
		wait_(philo->table->time_of_eat * 2);
	if (philo->table->num_of_philo % 2 == 0 && philo->id % 2 == 0)
		wait_(philo->table->time_of_eat);
	while (1)
	{
		philo_pickup_fork(philo);
		if (philo->table->num_of_philo == 1)
			break ;
		if (philo_eating(philo) == 1)
			break ;
		if (philo->id % 2 == 0)
			wait_(2);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (NULL);
}

int	run(int ac, char **av)
{
	t_table		*table;
	t_philo		*philo;
	int			i;
	int			num;

	if (ft_check(ac, av))
		return (1);
	table = get_info(ac, av);
	if (!table)
		return (2);
	philo = init_philo(table);
	if (!philo)
		return (2);
	num = table->num_of_philo;
	i = -1;
	while (++i < table->num_of_philo)
		pthread_create(&philo[i].thread, NULL, philosophers, &(philo[i]));
	monitor(table, philo, num);
	free_all_arg(table, philo, num);
	return (0);
}

int	main(int ac, char **av)
{
	int	signal;

	signal = 0;
	if (ac == 5 || ac == 6)
	{
		signal = run(ac, av);
		if (!signal)
			return (0);
		if (signal == 1)
			printf("INVALID VALUE\n");
		else if (signal == 2)
			printf("ALLOCATE FAILED\n");
	}
	else
		printf("AGUMENT ERROR\n");
	return (1);
}
