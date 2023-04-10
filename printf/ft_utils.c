/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:42:31 by dongkseo          #+#    #+#             */
/*   Updated: 2023/03/20 21:35:56 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_v2(long long nb, int *count, const char *base, int baselen)
{
	if (nb < 0)
	{
		*count += write(1, "-", 1);
		nb *= -1;
	}
	if (nb > baselen - 1)
		ft_putnbr_v2(nb / baselen, count, base, baselen);
	*count += write(1, &base[nb % baselen], 1);
	return (*count);
}

int	ft_putstr_v2(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (str == NULL)
	{
		write (1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		count++;
		write(1, &str[i], 1);
		i++;
	}
	return (count);
}

void	ft_hexprint(unsigned long long nb, int *lev, char *hexbase)
{
	if (nb > 15)
		ft_hexprint(nb / 16, lev, hexbase);
	hexbase[*lev] = "0123456789abcdef"[nb % 16];
	*lev += 1;
}

int	ft_printf_memory(void *address)
{
	unsigned long long	*addr;
	int					lev;
	char				hexbase[13];

	lev = 0;
	addr = (unsigned long long *)address;
	ft_bzero(hexbase, sizeof(hexbase));
	ft_memset(hexbase, '0', sizeof(hexbase));
	write(1, "0x", 2);
	ft_hexprint((unsigned long long)addr, &lev, hexbase);
	hexbase[lev] = '\0';
	return (ft_putstr_v2(hexbase) + 2);
}

int	ft_putchar_v2(char c)
{
	return (write(1, &c, 1));
}
