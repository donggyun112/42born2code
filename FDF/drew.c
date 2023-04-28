/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drew.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:01:42 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/22 05:39:10 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw(t_vars *var)
{
	var->image->image = mlx_new_image(var->mlx, 1100, 800);
	var->image->addr = mlx_get_data_addr(var->image->image, \
	&var->image->bit_pixel, &var->image->bit_sizeline, \
	&var->image->bit_endian);
	put_map_w(var->map, var->image);
	mlx_put_image_to_window(var->mlx, var->mlx_win, \
	var->image->image, 0, 0);
}

void	drew_line(int st_y, int en_x, int en_y, t_image *image)
{
	t_data	xy;

	xy.len = image->len;
	xy.size = image->w_size;
	set_start_point(image->st_x, st_y, &xy);
	set_end_point(en_x, en_y, &xy);
	bresenham(xy, image, image->color);
}

void	drew_line2(t_map_data **map, t_image *image, int i)
{
	image->st_x = get_x_p(map[i]->x, i, image);
	drew_line(get_y_p(map[i]->x, i, image) + map[i]->z * image->y_volume, \
	get_x_p(map[i]->next->x, i, image), \
	get_y_p(map[i]->next->x, i, image) + map[i]->next->z * \
	image->y_volume, image);
	image->st_x = get_x_p(map[i + 1]->x, i + 1, image);
	drew_line(get_y_p(map[i + 1]->x, i + 1, image) + map[i + 1]->z * \
	image->y_volume, get_x_p(map[i + 1]->next->x, i + 1, image), \
	get_y_p(map[i + 1]->next->x, i + 1, image) + map[i + 1]->next->z * \
	image->y_volume, image);
	image->st_x = get_x_p(map[i]->x, i, image);
	drew_line(get_y_p(map[i]->x, i, image) + map[i]->z * image->y_volume, \
	get_x_p(map[i + 1]->x, i + 1, image), \
	get_y_p(map[i + 1]->x, i + 1, image) + map[i + 1]->z * \
	image->y_volume, image);
	image->st_x = get_x_p(map[i]->next->x, i, image);
	drew_line(get_y_p(map[i]->next->x, i, image) + map[i]->next->z * \
	image->y_volume, \
	get_x_p(map[i + 1]->next->x, i + 1, image), \
	get_y_p(map[i + 1]->next->x, i + 1, image) + map[i + 1]->next->z * \
	image->y_volume, image);
}

t_map_data	**read_map(char **av, t_image *image, int flag)
{
	t_tools		tools;
	t_map_data	**map;
	int			x;

	tools.s = image_size_(flag, av, image);
	tools.fd = open(av[1], O_RDONLY);
	if (tools.fd == -1)
		error_("fd Error");
	set_image_data(image, tools);
	map = make_map(tools);
	while (1)
	{
		tools.line = get_next_line(tools.fd);
		if (!tools.line)
			break ;
		tools.split_map = ft_split(tools.line, 32);
		free(tools.line);
		x = -1;
		while (tools.split_map[++x])
			push(&map[tools.s], x + 5, atoi(tools.split_map[x]) * 1.2, \
			find_color(tools.split_map[x]));
		array_clear(tools.split_map);
		tools.s--;
	}
	return (map);
}

void	put_map_w(t_map_data **map, t_image *image)
{
	t_map_data	*tmp;
	t_map_data	*back;
	int			i;

	i = 0;
	while (i < image->size / 50)
	{
		tmp = map[i + 1];
		back = map[i];
		while (map[i]->next && map[i + 1]->next)
		{
			image->color = map[i]->color;
			drew_line2(map, image, i);
			map[i] = map[i]->next;
			map[i + 1] = map[i + 1]->next;
		}
		map[i] = back;
		map[i + 1] = tmp;
		i++;
	}
}
