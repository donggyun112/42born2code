/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controle_keybord.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:07:22 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/21 22:37:36 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, t_vars *vars)
{
	if (keycode < 256)
		vars->keys[keycode] = TRUE;
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
	if (keycode < 256)
		vars->keys[keycode] = FALSE;
	return (0);
}

void	check_controle(t_vars *var)
{
	if (var->keys[K] || var->keys[L])
	{
		var->image->len += (get_x_p(var->image->zoom_x, 0, var->image) \
			* 1.22322);
		var->image->w_size -= (get_y_p(0, var->image->zoom_y, var->image) \
			* 0.5981);
		if (var->keys[K])
		{
			var->image->ang_a += 0.02;
			var->image->ang_b += 0.02;
		}
		else
		{
			var->image->ang_a -= 0.02;
			var->image->ang_b -= 0.02;
		}
		var->image->zoom_y = 0;
		var->image->zoom_x = 0;
	}
}

void	zoom(t_vars *var)
{
	if (var->keys[PLUS])
	{
		var->image->volume *= 1.05;
		var->image->y_volume *= 1.05;
	}
	else if (var->keys[MINUS])
	{
		var->image->volume *= 0.9;
		var->image->y_volume *= 0.9;
	}
}

int	loop_hook(t_vars *var)
{
	if (var->keys[ESC])
	{
		mlx_destroy_window(var->mlx, var->mlx_win);
		exit(0);
	}
	if (var->keys[UP])
		var->image->zoom_y += 3;
	else if (var->keys[DOWN])
		var->image->zoom_y -= 3;
	else if (var->keys[LEFT])
		var->image->zoom_x -= 1;
	else if (var->keys[RIGHT])
		var->image->zoom_x += 1;
	else if (var->keys[L] || var->keys[K])
		check_controle(var);
	else if (var->keys[PLUS] || var->keys[MINUS])
		zoom(var);
	else if (var->keys[H])
		var->image->z_rota = 100;
	else if (var->keys[J])
		var->image->z_rota = 1;
	else
		return (0);
	draw(var);
	return (0);
}
