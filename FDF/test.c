#include <math.h>
#include <stdlib.h>
#include "mlx_mms/mlx.h"

typedef struct image
{
	void	*image;
	char	*addr;
	int		bit_pixel;
	int		bit_sizeline;
	int		bit_endian;
}image;

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
}	t_vars;

typedef struct s_bresenham
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	p;
	int	inc_x;
	int	inc_y;
}	t_bresenham;

typedef struct s_data
{
	int start_x;
	int end_x;
	int start_y;
	int end_y;
}	t_data;



int	_x(int x)
{
	return (x + 600);
}

int	_y(int y)
{
	y *= -1;
	return (y + 400);
}

void	set_start_point(int x, int y, t_data *data)
{
	data->start_x = _x(x);
	data->start_y = _y(y);
}

void	set_end_point(int x, int y, t_data *data)
{
	data->end_x = _x(x);
	data->end_y = _y(y);
}

void	my_mlx_pixel_put(image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + ((y * data->bit_sizeline) + (x * (data->bit_pixel / 8)));
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

void	bresenham_1_1(t_bresenham data, t_data val, image *image, int color)
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

void	bresenham_1_2(t_bresenham data, t_data val, image *image, int color)
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

void	bresenham_1(t_bresenham data, t_data val, image *image, int color)
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

void	bresenham2_1(t_bresenham data, t_data val, image *image, int color)
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

void	bresenham2_2(t_bresenham data, t_data val, image *image, int color)
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

void	bresenham2(t_bresenham data, t_data val, image *image, int color)
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

void	bresenham(t_data val, image *image, int color)
{
	t_bresenham	data;

	data.dx = abs(val.end_x - val.start_x);
	data.dy = abs(val.end_y - val.start_y);
	if (data.dy <= data.dx)
	{
		bresenham_1(data, val, image, color);
	}
	else
	{
		bresenham2(data, val, image, color);
	}
}


int main()
{
	t_vars	var;
	image	data;
	t_data	xy;

	var.mlx = mlx_init();
	var.mlx_win = mlx_new_window(var.mlx, 1200, 800, "test");
	data.image = mlx_new_image(var.mlx, 1200, 800);
	data.addr = mlx_get_data_addr(data.image, &data.bit_pixel, &data.bit_sizeline, &data.bit_endian); // 없이도 화면에 점을 찍을 수 있습니다.
	/* for (int x = -300; x < 300; x++)
		my_mlx_pixel_put(&data, _x(x), _y(x), 0x00FF0000);
	for (int x = -300; x < 300; x++)
		my_mlx_pixel_put(&data, _x(x), _y(-x), 0x00FF0000);*/
	set_start_point(0, 300, &xy);
	set_end_point(0, -300, &xy);
	bresenham(xy, &data, 0x00FF0000);
	set_start_point(300, 0, &xy);
	set_end_point(-300, 0, &xy);
	bresenham(xy, &data, 0x00FF0000);
	set_start_point(16, 22, &xy);
	set_end_point(-150, 100, &xy);
	bresenham(xy, &data, 0x00FF0000);
	mlx_put_image_to_window(var.mlx, var.mlx_win, data.image, 0, 0);
	mlx_key_hook(var.mlx_win, key_hook, &var);
	mlx_loop(var.mlx);
}