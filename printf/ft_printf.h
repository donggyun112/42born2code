/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:36:49 by dongkseo          #+#    #+#             */
/*   Updated: 2023/03/21 14:31:52 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_putnbr_v2(long long nb, int *count, const char base[], int baselen);
int		ft_putstr_v2(const char *str);
void	ft_bzero(void *ptr, size_t num);
int		ft_printf_memory(void *address);
int		ft_check_format(const char format, va_list args);
int		ft_processing(const char *format, va_list args);
int		ft_printf(const char *format, ...);
void	*ft_memset(void *ptr, int value, size_t num);
void	ft_hexprint(unsigned long long nb, int *lev, char *hexbase);
int		ft_putnbr_v2(long long nb, int *count, const char *base, int baselen);
int		ft_putstr_v2(const char *str);
void	ft_hexprint(unsigned long long nb, int *lev, char *hexbase);
int		ft_printf_memory(void *address);
int		ft_putchar_v2(char c);

#endif
