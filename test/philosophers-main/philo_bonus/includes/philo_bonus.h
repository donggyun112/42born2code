/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongmpa <seongmpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 01:10:28 by seongmpa          #+#    #+#             */
/*   Updated: 2023/03/30 18:05:39 by seongmpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>

typedef struct s_philo
{
	struct s_table	*table;
	pid_t			pid;
	int				id;
	int				eat_count;
	int				must_eat_time;
	long long		start_time;
	long long		last_eat_time;
	int				left;
	int				right;
}				t_philo;

typedef struct s_table
{
	struct s_philo	*philo;
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_time;
	int				finish;
	int				count;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*table_lock;
}				t_table;

/* init part */
t_table		*init_table_arg(char **argv, int num);
t_table		*init_table(char **argv, int num);
t_philo		*init_philo(int num, t_table *table, char **argv);
char		**make_str(char **argv);

/* util part */
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
char		**ft_split(char const *s, char c);
int			check_str(int argc, char **str);
int			print_error(char *str, int errno);
long long	get_time(void);
void		philo_pass_time(long long time);
void		philo_print(t_philo *philo, char *str, int flag);
void		ft_waitpid(t_philo *philo, t_table *table, int num);
void		unlink_sem(t_table *table);
void		free_all_arg(t_philo *philo, t_table *table, char **str);
int			check_size_double_array(char **str);

/* act part */
void		philosophers(t_philo *philo, t_table *table);
void		*monitoring(void *param);

#endif