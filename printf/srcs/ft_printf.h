# ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <unistd.h>

int	ft_putnbr_v2(long long nb, int *count, const char base[], int baselen);
int	ft_putstr_v2(const char *str);
void	ft_hexprint(unsigned long long nb, int *lev, char *hexbase);
int	ft_printf_memory(void *address);
int	ft_check_format(const char format, va_list args);
int	ft_processing(const char *format, va_list args);
int	ft_printf(const char *format, ...);
void* ft_memset(void* ptr, int value, size_t num);
void	ft_bzero(void *ptr, size_t num);

#endif
