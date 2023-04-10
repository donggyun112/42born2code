#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>

// mlx 구조체 mlx 포인터와 생성할 win 포인터를 가지고 있다.
typedef struct	s_vars {
	void		*mlx;
	void		*win;
}				t_vars;

//이미지의 정보를 나타내는 변수를 저장한 구조체
typedef struct s_data
{
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

//원하는 좌표에 해당하는 주소에 color값을 넣는 함수
void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// esc key press event
int	key_hook(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int main()
{
	t_vars vars;
	t_data image;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "Hellow World!");
	image.img = mlx_new_image(vars.mlx, 500, 500); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당
	for (int i = 0 ; i < 500 ; i++)
	{
		for (int j = 0 ; j < 500 ; j++)
		{
			my_mlx_pixel_put(&image, i, i, 0x00FF0000);
		}	
	}
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars); // esc key press event
	mlx_loop(vars.mlx);
	return (0);
}