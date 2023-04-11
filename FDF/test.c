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

typedef struct	s_vars
{
	void	*mlx;
	void	*mlx_win;
}	t_vars;

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

int	_x(int x)
{
	return (x + 600);
}

int	_y(int y)
{
	return (y + 400);
}

int main()
{
	t_vars	var;
	image	data;

	var.mlx = mlx_init();
	var.mlx_win = mlx_new_window(var.mlx, 1200, 800, "test");
	data.image = mlx_new_image(var.mlx, 1200, 800);
	data.addr = mlx_get_data_addr(data.image, &data.bit_pixel, &data.bit_sizeline, &data.bit_endian); // 없이도 화면에 점을 찍을 수 있습니다.
	for (int x = -300; x < 300; x++)
		my_mlx_pixel_put(&data, _x(x), _y(x), 0x00FF0000);
	for (int x = -300; x < 300; x++)
		my_mlx_pixel_put(&data, _x(x), _y(-x), 0x00FF0000);
	for (int x = -300; x < 300; x++)
		my_mlx_pixel_put(&data, _x(x), _y(0), 0x00FF0000);
	for (int x = -300; x < 300; x++)
		my_mlx_pixel_put(&data, _x(0), _y(x), 0x00FF0000);		
	mlx_put_image_to_window(var.mlx, var.mlx_win, data.image, 0, 0);
	mlx_key_hook(var.mlx_win, key_hook, &var);
	mlx_loop(var.mlx);
}