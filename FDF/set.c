/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:10:16 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/21 21:59:11 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_var(t_vars *var)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		var->keys[i] = 0;
		i++;
	}
	var->image->ang_a = 0.65;
	var->image->ang_b = 0.65;
	var->zoom_level = 1;
	var->left_click_pressed = 0;
	var->right_click_pressed = 0;
	var->image->zoom_x = 0;
	var->image->zoom_y = 0;
}

t_map_data	**make_map(t_tools tools)
{
	t_map_data	**map;
	int			x;

	x = 0;
	map = (t_map_data **)malloc(sizeof(t_map_data *) * (tools.s + 2));
	while (x < tools.s + 2)
	{
		map[x] = NULL;
		x++;
	}
	return (map);
}

void	set_start_point(int x, int y, t_data *data)
{
	data->start_x = _x(x, data->len);
	data->start_y = _y(y, data->size);
}

void	set_end_point(int x, int y, t_data *data)
{
	data->end_x = _x(x, data->len);
	data->end_y = _y(y, data->size);
}

void	set_image_data(t_image *image, t_tools tools)
{
	image->w_size = 800;
	image->len = 1100;
	image->size = tools.s * 50;
}
