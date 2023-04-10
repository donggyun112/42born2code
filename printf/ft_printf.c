/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:37:58 by dongkseo          #+#    #+#             */
/*   Updated: 2023/03/28 01:24:37 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
typedef struct node
{
	struct node *next;
}	t_node;

int	ft_check_format(const char format, va_list args)
{
	int			count;
	const char	*b_16 = "0123456789abcdef";
	const char	*b_16_2 = "0123456789ABCDEF";
	const char	*b10 = "0123456789";

	count = 0;
	if (format == 'c')
		count = ft_putchar_v2(va_arg(args, int));
	else if (format == 's')
		count = ft_putstr_v2(va_arg(args, char *));
	else if (format == 'p')
		count = ft_printf_memory(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		count = ft_putnbr_v2(va_arg(args, int), &count, b10, 10);
	else if (format == 'u')
		count = ft_putnbr_v2(va_arg(args, unsigned int), &count, b10, 10);
	else if (format == 'x')
		count = ft_putnbr_v2(va_arg(args, unsigned int), &count, b_16, 16);
	else if (format == 'X')
		count = ft_putnbr_v2(va_arg(args, unsigned int), &count, b_16_2, 16);
	else if (format == '%')
		count = ft_putchar_v2('%');
	return (count);
}

int	ft_processing(const char *format, va_list args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_check_format(format[i], args);
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	count = ft_processing(format, args);
	va_end(args);
	return (count);
}

int main()
{
	int a;
	ft_printf("abc%d", a);
}

void test(int a, int b, int* c);
