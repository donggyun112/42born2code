/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinat_correction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:19:09 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/21 22:37:10 by dongkseo         ###   ########.fr       */
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

float	get_y_p(int x, float y, t_image *image)
{
	double	ang;
	float	z_rotate;

	ang = image->ang_b;
	z_rotate = image->z_rota;
	x *= image->volume;
	y += image->zoom_y;
	y *= image->volume;
	return ((sin(ang) * x + cos(ang) * y) / z_rotate);
}

float	get_x_p(int x, float y, t_image *image)
{
	double	ang;
	float	volume;

	ang = image->ang_a;
	volume = 2;
	x += image->zoom_x;
	x *= image->volume;
	y *= image->volume;
	return ((cos(ang) * x - sin(ang) * y) * volume);
}
