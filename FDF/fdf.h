/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:45:00 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/20 23:21:20 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_map_data
{
	float				x;
	float				z;
	struct s_map_data	*next;
}	t_map_data;

typedef struct s_image
{
	void		*image;
	char		*addr;
	int			bit_pixel;
	int			bit_sizeline;
	int			bit_endian;
	int			size;
	float		len;
	float		w_size;
	int			color;
	int			defult_color;
	double		volume;
	double		y_volume;
	double		ang_a;
	double		ang_b;
	double		zoom_y;
	double		zoom_x;
	double		tmp1;
	double		tmp2;
	int			st_x;
}	t_image;

typedef struct s_vars
{
	t_image		*image;
	void		*mlx;
	void		*mlx_win;
	int			ac;
	char		**av;
	t_map_data	**map;
	double		zoom_level;
	int			keys[256];
	int			mouse[10];
	int			left_click_pressed;
	int			right_click_pressed;
	int			mouse_x;
	int			mouse_y;
	int			mouse_p_x;
	int			mouse_p_y;
}	t_vars;

typedef struct s_bresenham
{
	int		x;
	int		y;
	float	dx;
	float	dy;
	int		p;
	int		inc_x;
	int		inc_y;
}	t_bresenham;

typedef struct s_data
{
	float	start_x;
	float	end_x;
	float	start_y;
	float	end_y;
	int		size;
	int		len;
}	t_data;

typedef struct s_tools
{
	int		fd;
	int		s;
	char	*line;
	char	**split_map;
}	t_tools;

typedef struct s_drew
{
	int	st_x;
	int	st_y;
	int	en_x;
	int	en_y;
}	t_drew;

# define UP			126
# define DOWN		125
# define LEFT		123
# define RIGHT		124
# define ESC		53
# define KEYPRESS	02
# define TRUE		1
# define FALSE		0
# define MOUSE_LEFT_BUTTON	1
# define MOUSE_RIGHT_BUTTON	2
# define MOUSE_THIRD_BUTTON	3
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5
# define MOUSE_SCROLL_LEFT	6
# define MOUSE_SCROLL_RIGHT	7
# define J 38
# define L 37
# define K 40
# define PLUS 24
# define MINUS 27

# include <math.h>
# include <stdlib.h>
# include "mlx_mms/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"

// mlx_hook
void	engine(t_vars *var);
int		mouse_press(int button, int x, int y, t_vars *var);
int		mouse_release(int mouse_code, int x, int y, t_vars *var);
int		mouse_motion(int x, int y, t_vars *var);
int		key_press(int keycode, t_vars *vars);
int		key_release(int keycode, t_vars *vars);
int		loop_hook(t_vars *var);
int		close_(void *param);
void	zoom(t_vars *var);
void	check_controle(t_vars *var);

//draw
void	draw(t_vars *var);
void	drew_line(int st_y, int en_x, int en_y, t_image *image);
void	drew_line2(t_map_data **map, t_image *image, int i);
void	put_map_w(t_map_data **map, t_image *image);
void	bresenham(t_data val, t_image *image, int color);
void	bresenham2(t_bresenham data, t_data val, t_image *image, int color);
void	bresenham2_2(t_bresenham data, t_data val, t_image *image, int color);
void	bresenham2_1(t_bresenham data, t_data val, t_image *image, int color);
void	bresenham_1(t_bresenham data, t_data val, t_image *image, int color);
void	bresenham_1_2(t_bresenham data, t_data val, t_image *image, int color);
void	bresenham_1_1(t_bresenham data, t_data val, t_image *image, int color);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
t_map_data	**read_map(int ac, char **av, t_image *image, int flag);
//setting
void		set_var(t_vars *var);
void		set_image_data(t_image *image, t_tools tools);
void		set_end_point(int x, int y, t_data *data);
void		set_start_point(int x, int y, t_data *data);
t_map_data	**make_map(t_tools tools);
//Coordinate correction
float	_y(int y, int size);
float	_x(int x, int len);
float	get_y_p(int x, float y, t_image *image);
float	get_x_p(int x, float y, t_image *image);
//tools
void	push(t_map_data **map, float x, float z);
int		image_size_(int flag, char **av, t_image *image);
int		map_size(char **av);
#endif