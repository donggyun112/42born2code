#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

typedef struct s_table
{
	int	num_of_philo;
	int	time_of_die;
	int	time_of_eat;
	int	time_of_sleep;
	int	limit_of_eat;
	int	finish;
	long long start_time;
	pthread_mutex_t *name;
	pthread_mutex_t print_mutex;
	pthread_mutex_t finish_mutex;
	pthread_mutex_t time_mutex;
	pthread_mutex_t eat_mutex;
	pthread_t monitoring;
}	t_table;

typedef struct s_philo
{
	int	id;
	int num_eaten;
	int				left_fork;
	int				right_fork;
	long long		last_eat;
	long long		start_time;
	int				finish;
	struct s_table	*table;
	pthread_t thread;
}	t_philo;

int		ft_atoi(const char *str);

#endif