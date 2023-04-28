/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controle_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:05:31 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/21 20:38:46 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_release(int mouse_code, int x, int y, t_vars *var)
{
	(void)x;
	(void)y;
	if (mouse_code == 2)
	{
		var->right_click_pressed = 0;
	}
	if (mouse_code == 1)
	{
		var->left_click_pressed = 0;
	}
	return (0);
}

int	mouse_motion(int x, int y, t_vars *var)
{
	var->mouse_p_x = var->mouse_x;
	var->mouse_p_y = var->mouse_y;
	var->mouse_x = x;
	var->mouse_y = y;
	if (var->right_click_pressed)
	{
		var->image->len += (get_x_p(var->image->zoom_x, 0, var->image) \
			* 1.22322);
		if (var->image->zoom_y)
			var->image->w_size -= (get_y_p(0, var->image->zoom_y, var->image) \
			* 0.5981);
		var->image->zoom_y = 0;
		var->image->zoom_x = 0;
		var->image->ang_a += (x - var->mouse_p_x) * 0.002;
		var->image->ang_b += (x - var->mouse_p_x) * 0.002;
	}
	if (var->left_click_pressed)
	{
		var->image->zoom_x += (x - var->mouse_p_x) * 0.1;
		var->image->zoom_y -= (y - var->mouse_p_y) * 0.2;
	}
	if (var->left_click_pressed || var->right_click_pressed)
		draw(var);
	return (0);
}

int	mouse_press(int button, int x, int y, t_vars *var)
{
	(void)x;
	(void)y;
	if (button == 4 || button == 5)
	{
		if (button == 4)
		{
			var->image->volume *= 1.1;
			var->image->y_volume *= 1.1;
		}
		else if (button == 5)
		{
			var->image->volume *= 0.9;
			var->image->y_volume *= 0.9;
		}
	}
	if (button == 2)
		var->right_click_pressed = 1;
	if (button == 1)
		var->left_click_pressed = 1;
	var->image->image = mlx_new_image(var->mlx, 1100, 800);
	var->image->addr = mlx_get_data_addr(var->image->image, \
	&var->image->bit_pixel, &var->image->bit_sizeline, &var->image->bit_endian);
	put_map_w(var->map, var->image);
	mlx_put_image_to_window(var->mlx, var->mlx_win, var->image->image, 0, 0);
	return (0);
}
