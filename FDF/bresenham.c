/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:03:19 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/21 20:29:41 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham(t_data val, t_image *image, int color)
{
	t_bresenham	data;

	data.dx = fabsf(val.end_x - val.start_x);
	data.dy = fabsf(val.end_y - val.start_y);
	if (data.dy <= data.dx)
	{
		bresenham_1(data, val, image, color);
	}
	else
	{
		bresenham2(data, val, image, color);
	}
}

void	bresenham2(t_bresenham data, t_data val, t_image *image, int color)
{
	data.p = 2 * (data.dx - data.dy);
	data.x = val.start_x;
	data.inc_x = 1;
	if (val.end_x < val.start_x)
		data.inc_x = -1;
	data.inc_y = 1;
	if (val.end_y < val.start_y)
		data.inc_y = -1;
	data.y = val.start_y;
	if (val.start_y <= val.end_y)
		bresenham2_1(data, val, image, color);
	else
		bresenham2_2(data, val, image, color);
}

void	bresenham2_1(t_bresenham data, t_data val, t_image *image, int color)
{
	while (data.y <= val.end_y)
	{
		my_mlx_pixel_put(image, data.x, data.y, color);
		if (0 >= data.p)
			data.p += 2 * data.dx;
		else
		{
			data.p += 2 * (data.dx - data.dy);
			data.x += data.inc_x;
		}
		data.y += data.inc_y;
	}
}

void	bresenham2_2(t_bresenham data, t_data val, t_image *image, int color)
{
	while (data.y >= val.end_y)
	{
		my_mlx_pixel_put(image, data.x, data.y, color);
		if (0 >= data.p)
			data.p += 2 * data.dx;
		else
		{
			data.p += 2 * (data.dx - data.dy);
			data.x += data.inc_x;
		}
		data.y += data.inc_y;
	}
}
