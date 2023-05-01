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
	int	count;
	int	finish_eat;
	long long start_time;
	pthread_mutex_t *name;
	pthread_mutex_t print_mutex;
	pthread_mutex_t	safe;
	pthread_t monitoring;
	struct s_philo	*philo;
}	t_table;

typedef struct s_philo
{
	int	id;
	int num_eaten;
	int				left;
	int				right;
	int				must_eat;
	long long		last_eat;
	long long		start_time;
	struct s_table	*table;
	pthread_t thread;
}	t_philo;

int		ft_atoi(const char *str);

#define DIED 1
#define END_OF_EAT 0

#endif