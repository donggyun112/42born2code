#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	putnbr(long long nb, int *count)
{
	if (nb < 0)
	{
		nb *= -1;
		*count += write(1, "-", 1);
	}
	if (nb > 9)
		putnbr(nb / 10, count);
	*count += write(1, &"0123456789"[nb % 10], 1);
}

void	putnbr16(long long nb, int *count)
{
	if (nb > 15)
		putnbr16(nb / 16, count);
	*count += write(1, &"0123456789abcdef"[nb % 16], 1);
}

int putstr(char *str)
{
	int count = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*str)
		count += write(1, str++, 1);
	return (count);
}
	

int	ft_printf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int i = 0;
	int	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 'd')
				putnbr(va_arg(ap, int), &count);
			if (format[i] == 's')
				count += putstr(va_arg(ap, char *));
			if (format[i] == 'x')
				putnbr16(va_arg(ap, unsigned int), &count);
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}
