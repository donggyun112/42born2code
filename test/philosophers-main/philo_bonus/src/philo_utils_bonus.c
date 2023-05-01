/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongmpa <seongmpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 01:22:31 by seongmpa          #+#    #+#             */
/*   Updated: 2023/03/30 18:04:47 by seongmpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			num = num * 10 + (*str - '0');
		else
			break ;
		str++;
	}
	return (num * sign);
}

int	check_str(int argc, char **str)
{
	int	i;
	int	j;
	int	num;

	(void)argc;
	i = 0;
	num = check_size_double_array(str);
	if (num != 5 && num != 6)
		return (-1);
	while (++i < num)
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] < '0' || str[i][j] > '9')
				return (-1);
		}
		if (ft_atoi(str[i]) < 1 || ft_atoi(str[i]) > 2147483647)
			return (-1);
	}
	return (0);
}

int	print_error(char *str, int errno)
{
	printf("%s\n", str);
	return (errno);
}

long long	get_time(void)
{
	long long		result;
	struct timeval	time;

	gettimeofday(&time, NULL);
	result = (long long)(time.tv_sec * 1000) + (long long)(time.tv_usec / 1000);
	return (result);
}

void	philo_pass_time(long long time)
{
	long long		dest_time;

	dest_time = get_time() + time;
	while (get_time() < dest_time)
		usleep(100);
}
