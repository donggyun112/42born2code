/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 00:25:03 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/22 01:52:45 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_hex(int c)
{
	const char	*hex = "0123456789ABCDEF";
	const char	*hex2 = "0123456789abcdef";
	int			i;

	i = 0;
	while (hex[i])
	{
		if (hex[i] == c)
			return (i);
		if (hex2[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

size_t	atoi_hex(char *str)
{
	int		sum;
	int		i;

	sum = 0;
	i = 0;
	while (str[i] && is_hex(str[i]) != -1)
	{
		sum = sum * 16 + is_hex(str[i]);
		i++;
	}
	return (sum);
}

size_t	find_color(char *line)
{
	int			i;
	size_t		color;

	i = 0;
	while (line[i] && line[i] != ',')
		i++;
	if (line[i] == ',')
		i++;
	else
		return (0xFFFFFF);
	color = atoi_hex(&line[i + 2]);
	return (color);
}
