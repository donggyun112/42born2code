/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:40:40 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/02 21:41:44 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoi(const char *str)
{
	int	sum;
	int	sign;

	sum = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - '0');
		str++;
	}
	return (sum * sign);
}

int	nb_len(long long nb)
{
	int	length;

	length = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		length++;
	}
	return (length);
}

void	write_int(long long nb, char *arr, int *lev)
{
	if (nb > 9)
		write_int(nb / 10, arr, lev);
	arr[*lev] = (nb % 10 + '0');
	*lev += 1;
}

char	*ft_itoa(int n)
{
	long long	nb;
	int			lev;
	char		*arr;

	nb = (long long)n;
	lev = 0;
	if (nb < 0)
	{
		nb *= -1;
		lev = 1;
		arr = (char *)malloc(nb_len(nb) + 2);
		if (!arr)
			return (NULL);
		arr[0] = '-';
	}
	else
		arr = (char *)malloc(nb_len(nb) + 1);
	if (!arr)
		return (NULL);
	write_int(nb, arr, &lev);
	arr[lev] = '\0';
	return (arr);
}
