/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinat_correction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:19:09 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/21 00:29:39 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	_x(int x, int len)
{
	return (x + len / 2.5);
}

float	_y(int y, int size)
{
	y *= -1;
	return (y + size / 1.2);
}
