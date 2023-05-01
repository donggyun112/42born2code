/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongmpa <seongmpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 01:18:06 by seongmpa          #+#    #+#             */
/*   Updated: 2023/03/30 18:09:21 by seongmpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	main(int argc, char **argv)
{
	t_table		*table;
	t_philo		*philo;
	int			philo_num;
	int			i;
	char		**str;

	str = make_str(argv);
	if (check_str(argc, str) == -1)
		return (print_error("Invalid arguments.", 1));
	philo_num = ft_atoi(str[1]);
	table = init_table(str, philo_num);
	philo = init_philo(philo_num, table, str);
	i = -1;
	while (++i < philo_num)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			return (print_error("fork error", 1));
		else if (philo[i].pid == 0)
			philosophers(&philo[i], table);
	}
	ft_waitpid(philo, table, philo_num);
	unlink_sem(table);
	free_all_arg(philo, table, str);
	return (0);
}
