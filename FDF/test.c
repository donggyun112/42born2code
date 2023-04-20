/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:39:27 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/20 23:21:14 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	if (1095 < x || 795 < y || x < 0 || y < 0)
		return ;
	dst = data->addr + ((y * data->bit_sizeline) + (x * (data->bit_pixel / 8)));
	if (*(unsigned int *)dst != 0x000000)
		return ;
	*(unsigned int *)dst = color;
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

float	get_y_p(int x, float y, t_image *image)
{
	double	ang;
	float	z_rotate;

	ang = image->ang_b;
	z_rotate = 1;
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

void	drew_line(int st_y, int en_x, int en_y, t_image *image)
{
	t_data	xy;

	xy.len = image->len;
	xy.size = image->w_size;
	set_start_point(image->st_x, st_y, &xy);
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
	image->w_size = 800;
	image->len = 1100;
	image->size = tools.s * 50;
}

t_map_data **make_map(t_tools tools)
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

int	image_size_(int flag, char **av, t_image *image)
{
	if (flag == 0)
		return (map_size(av) - 1);
	else
		return (image->size / 50);
}

t_map_data	**read_map(int ac, char **av, t_image *image, int flag)
{
	t_tools		tools;
	t_map_data	**map;
	int			x;

	tools.s = image_size_(flag, av, image);
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
			image->color = 0x00FF0000 + map[i]->z + 0x01000000 * map[i]->z;
			if (map[i]->z < 20 && map[i]->next->z < 20 \
			&& map[i + 1]->z < 20 && map[i + 1]->next->z < 20)
				image->color = 0xFFFFFF;
			drew_line2(map, image, i);
			map[i] = map[i]->next;
			map[i + 1] = map[i + 1]->next;
		}
		map[i] = back;
		map[i + 1] = tmp;
		i++;
	}
}

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

int mouse_press(int button, int x, int y, t_vars *var)
{
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

int key_press(int keycode, t_vars *vars)
{
	if (keycode < 256)
		vars->keys[keycode] = TRUE;
	return (0);
}

int key_release(int keycode, t_vars *vars)
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

int loop_hook(t_vars *var)
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
	else
		return (0);
	draw(var);
	return (0);
}

int	mouse_release(int mouse_code, int x, int y, t_vars *var)
{
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

int		close_(void *param)
{
	(void)param;
	exit(0);
}

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

void	engine(t_vars *var)
{
	mlx_hook(var->mlx_win, 2, 1L << 0, key_press, var);
	mlx_hook(var->mlx_win, 3, 1L << 1, key_release, var);
	mlx_hook(var->mlx_win, 17, 0, close_, var);
	mlx_hook(var->mlx_win, 4, 1L << 2, mouse_press, var);
	mlx_hook(var->mlx_win, 5, 1L << 3, mouse_release, var);
	mlx_hook(var->mlx_win, 6, 1L << 7, mouse_motion, var);
	mlx_loop_hook(var->mlx, loop_hook, var);
}

int main(int ac, char **av)
{
	t_vars		var;
	t_image		data;
	t_data		xy;
	t_map_data	**map;

	var.mlx = mlx_init();
	var.mlx_win = mlx_new_window(var.mlx, 1100, 800, "fdf");
	data.image = mlx_new_image(var.mlx, 1100, 800);
	data.addr = mlx_get_data_addr(data.image, &data.bit_pixel, \
	&data.bit_sizeline, &data.bit_endian);
	var.image = &data;
	set_var(&var);
	data.volume = var.zoom_level;
	data.y_volume = 1;
	map = read_map(ac, av, &data, 0);
	put_map_w(map, &data);
	var.map = map;
	var.ac = ac;
	var.av = av;
	engine(&var);
	mlx_put_image_to_window(var.mlx, var.mlx_win, var.image->image, 0, 0);
	mlx_loop(var.mlx);
}

/* void	_mat_ini(float mat[3][3])
{
	for(int i = 0; i < 3; i ++){
		for (int j = 0; j < 3; j ++)
			mat[i][j] = 0;
	}
}

void	_mat_mul(float position[3], float mat[3][3])
{
	float	v[3];

	v[X] = 0;
	v[Y] = 0;
	v[Z] = 0;
	v[X] = mat[X][X] * position[X] + mat[X][Y] * position[Y] + mat[X][Z] * position[Z];
	//
	//
	position[X] = v[X];
	//
	//
}

void	_rot_x(t_points *points, float ang)
{
	float	mat[3][3];

	_mat_ini(mat);
	mat[X][X] = 1;
	mat[Y][Y] = cos(ang);
	mat[Y][Z] = -sin(ang);
	mat[Z][Y] = sin(ang);
	mat[Z][Z] = cos(ang);
	int i = 0;
	while (i < number_of_points)
	{
		_mat_mul(points[i].position);
		i++;
	}	
}

void	_rotation(t_points *points, float ang[3])
{
	_rot_x(points, ang[X]);
	_rot_y(points, ang[Y]);
	_rpt_z(points, ang[Z]);
} */
