/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongmpa <seongmpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:53:23 by seongmpa          #+#    #+#             */
/*   Updated: 2023/03/30 18:15:38 by seongmpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_print(t_philo *philo, char *str, int flag)
{
	sem_wait(philo->table->print);
	printf("%lld %d %s\n", get_time() - philo->start_time, philo->id, str);
	if (flag == 1)
		sem_post(philo->table->print);
}

void	ft_waitpid(t_philo *philo, t_table *table, int num)
{
	int	status;
	int	i;

	i = -1;
	while (++i < num)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			i = -1;
			while (++i < num)
				kill(philo[i].pid, SIGKILL);
			return ;
		}
		else if (WEXITSTATUS(status) == 0)
		{
			table->count++;
			if (table->count == table->num)
				printf("Every philosophers have a happy meal~\n");
		}
	}
}

void	unlink_sem(t_table *table)
{
	sem_close(table->print);
	sem_close(table->forks);
	sem_close(table->table_lock);
	sem_unlink("print");
	sem_unlink("table_lock");
	sem_unlink("forks");
}

void	free_all_arg(t_philo *philo, t_table *table, char **str)
{
	int	i;

	free(table);
	free(philo);
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	*monitoring(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		usleep(100);
		sem_wait(philo->table->table_lock);
		if (get_time() - philo->last_eat_time > philo->table->time_to_die)
		{
			philo_print(philo, "died", 0);
			exit(1);
		}
		sem_post(philo->table->table_lock);
	}
}
