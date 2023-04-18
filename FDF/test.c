/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:39:27 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/18 23:37:26 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "mlx_mms/mlx.h"
#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "test.h"

float	_x(int x, int len)
{
	return (x + len / 2.5);
}

float	_y(int y, int size)
{
	y *= -1;
	return (y + size / 1.2);
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

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	if (data->len <= x || data->w_size <= y || x <= 0 || y <= 0)
		return ;
	dst = data->addr + ((y * data->bit_sizeline) + (x * (data->bit_pixel / 8)));
	if (*(unsigned int *)dst != 0x000000)
		return ;
	*(unsigned int *)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(0);
	}
	return (0);
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

float	get_y_p(int x, int y)
{
	float	ang;
	float	z_rotate;

	ang = 0.75;
	z_rotate = 1;
	return ((sin(ang) * x + cos(ang) * y) / z_rotate);
}

float	get_x_p(int x, int y)
{
	float	ang;
	float	volume;

	ang = 0.75;
	volume = 2;
	return ((cos(ang) * x - sin(ang) * y) * volume);
}

void	drew_line(int st_x, int st_y, int en_x, int en_y, t_image *image)
{
	t_data	xy;

	xy.len = image->len;
	xy.size = image->w_size;
	set_start_point(st_x, st_y, &xy);
	set_end_point(en_x, en_y, &xy);
	bresenham(xy, image, image->color);
}

void	push(t_map_data **map, float x, float z)
{
	t_map_data	*tmp;

	tmp = *map;
	if (tmp == NULL)
	{
		*map = (t_map_data *)malloc(sizeof(t_map_data));
		(*map)->x = x;
		(*map)->z = z;
		(*map)->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_map_data *)malloc(sizeof(t_map_data));
		tmp->next->x = x;
		tmp->next->z = z;
		tmp->next->next = NULL;
	}
}

int	map_size(char **av)
{
	int		fd;
	char	*line;
	int		size;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	size = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		size++;
	}
	return (size);
	close(fd);
}

void	set_image_data(t_image *image, t_tools tools)
{
	//image->volume = image->zoom_level;
	image->w_size = 1200;
	image->len = 1500;
	image->size = tools.s * 50;
}

t_map_data **make_map(t_tools tools)
{
	t_map_data	**map;

	map = (t_map_data **)malloc(sizeof(t_map_data *) * (tools.s + 2));
	for (int x = 0; x < tools.s + 2; x++)
		map[x] = NULL;
	return (map);
}

t_map_data	**read_map(int ac, char **av, t_image *image, int flag)
{
	t_tools	tools;
	t_map_data	**map;
	int	x;
	if (flag == 0)
		tools.s = map_size(av) - 1;
	else
		tools.s = image->size / 50;
	tools.fd = open(av[1], O_RDONLY);
	set_image_data(image, tools);
	map = make_map(tools);
	while (1)
	{
		tools.line = get_next_line(tools.fd);
		if (!tools.line)
			break ;
		tools.split_map = ft_split(tools.line, 32);
		x = -1;
		while (tools.split_map[++x])
			push(&map[tools.s], x, atoi(tools.split_map[x]) * 3);
		x = -1;
		while (tools.split_map[++x])
			free(tools.split_map[x]);
		tools.s--;
		free(tools.line);
	}
	return (map);
}

#include <stdio.h>

void	put_map_w(t_map_data **map, t_image *image)
{
	t_map_data *tmp;
	t_map_data *back;

	for (int i = 0; i < image->size / 50; i++)
	{
		tmp = map[i + 1];
		back = map[i];
		while (map[i]->next)
		{
			if (!map[i]->next->next)
				break ;
			int test = (int)map[i]->z;
			image->color = 0x00FFFFFF + 0x01000000 * (test);
			//printf("color : %x\n", image->color);
			drew_line(get_x_p(map[i]->x * image->volume, i * image->volume), get_y_p(map[i]->x * image->volume, i * image->volume) + map[i]->z, get_x_p(map[i]->next->x * image->volume, i * image->volume), get_y_p(map[i]->next->x * image->volume, i * image->volume) + map[i]->next->z, image);
			drew_line(get_x_p(map[i + 1]->x * image->volume, (i + 1) * image->volume), get_y_p(map[i + 1]->x * image->volume, (i + 1) * image->volume) + map[i + 1]->z, get_x_p(map[i + 1]->next->x * image->volume, (i + 1) * image->volume), get_y_p(map[i + 1]->next->x * image->volume, (i + 1) * image->volume) + map[i + 1]->next->z, image);
			drew_line(get_x_p(map[i]->x * image->volume, i * image->volume), get_y_p(map[i]->x * image->volume, i * image->volume) + map[i]->z, get_x_p(map[i + 1]->x * image->volume, (i + 1) * image->volume), get_y_p(map[i + 1]->x * image->volume, (i + 1) * image->volume) + map[i + 1]->z, image);
			drew_line(get_x_p(map[i]->next->x * image->volume, i * image->volume), get_y_p(map[i]->next->x * image->volume, i * image->volume) + map[i]->next->z, get_x_p(map[i + 1]->next->x * image->volume, (i + 1) * image->volume), get_y_p(map[i + 1]->next->x * image->volume, (i + 1) * image->volume) + map[i + 1]->next->z, image);
			map[i] = map[i]->next;
			map[i + 1] = map[i + 1]->next;
		}
		map[i] = back;
		map[i + 1] = tmp;
	}
}


int mouse_wheel_hook(int button, int x, int y, t_vars *var) 
{
    if (button == 4 || button == 5) 
	{
		
        if (button == 4) 
		{
			var->image->volume *= 1.1;
        } else if (button == 5) {
			var->image->volume *= 0.9;
        }
		var->image->image = mlx_new_image(var->mlx, 1500, 1200);
		var->image->addr = mlx_get_data_addr(var->image->image, &var->image->bit_pixel, &var->image->bit_sizeline, &var->image->bit_endian);
		put_map_w(var->map, var->image);
		mlx_put_image_to_window(var->mlx, var->mlx_win, var->image->image, 0, 0);
        return (1);
    }
    return 0;
}

int main(int ac, char **av)
{
	t_vars		var;
	t_image		data;
	t_data		xy;
	t_map_data	**map;

	var.mlx = mlx_init();
	var.mlx_win = mlx_new_window(var.mlx, 1500, 1200, "FDF");
	data.image = mlx_new_image(var.mlx, 1500, 1200);
	data.addr = mlx_get_data_addr(data.image, &data.bit_pixel, &data.bit_sizeline, &data.bit_endian);
	var.zoom_level = 1;
	data.volume = var.zoom_level;
	map = read_map(ac, av, &data, 0);
	put_map_w(map, &data);
	var.map = map;
	var.image = &data;
	var.ac = ac;
	var.av = av;
	mlx_put_image_to_window(var.mlx, var.mlx_win, data.image, 0, 0);
	mlx_key_hook(var.mlx_win, key_hook, &var);
	mlx_mouse_hook(var.mlx_win, mouse_wheel_hook, &var);
	mlx_loop(var.mlx);
}