/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:04:26 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/21 20:30:02 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham_1(t_bresenham data, t_data val, t_image *image, int color)
{
	data.p = 2 * (data.dy - data.dx);
	data.y = val.start_y;
	data.inc_x = 1;
	if (val.end_x < val.start_x)
		data.inc_x = -1;
	data.inc_y = 1;
	if (val.end_y < val.start_y)
		data.inc_y = -1;
	data.x = val.start_x;
	if (val.start_x <= val.end_x)
		bresenham_1_1(data, val, image, color);
	else
		bresenham_1_2(data, val, image, color);
}

void	bresenham_1_2(t_bresenham data, t_data val, t_image *image, int color)
{
	while (data.x >= val.end_x)
	{
		my_mlx_pixel_put(image, data.x, data.y, color);
		if (0 >= data.p)
			data.p += 2 * data.dy;
		else
		{
			data.p += 2 * (data.dy - data.dx);
			data.y += data.inc_y;
		}
		data.x += data.inc_x;
	}
}

void	bresenham_1_1(t_bresenham data, t_data val, t_image *image, int color)
{
	while (data.x <= val.end_x)
	{
		my_mlx_pixel_put(image, data.x, data.y, color);
		if (0 >= data.p)
			data.p += 2 * data.dy;
		else
		{
			data.p += 2 * (data.dy - data.dx);
			data.y += data.inc_y;
		}
		data.x += data.inc_x;
	}
}
