/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongmpa <seongmpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:15:21 by seongmpa          #+#    #+#             */
/*   Updated: 2023/03/30 18:02:20 by seongmpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	struct s_table	*table;
	pthread_t		tid;
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
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	table_lock;
}				t_table;

/* init part */
t_philo		*init_philo(int num, t_table *table);
t_table		*init_table(char **argv, int num);
t_table		*init_table_arg(char **argv, int num);
char		**make_str(char **argv);

/* act part */
void		*philosophers(void *param);

/* util part */
int			ft_atoi(const char *str);
int			check_str(char **str);
int			print_error(char *str, int errno);
long long	get_time(void);
void		philo_pass_time(long long time);
void		withdraw_all(t_table *table, int num);
void		philo_print(t_philo *philo, char *str, int flag);
int			check_size_double_array(char **str);
void		free_all_arg(t_table *table, t_philo *philo, int num, char **str);
char		**ft_split(char const *s, char c);
size_t		ft_strlen(const char *s);

#endif