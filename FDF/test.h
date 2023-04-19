#ifndef TEST_H
# define TEST_H

typedef struct s_image
{
	void		*image;
	char		*addr;
	int			bit_pixel;
	int			bit_sizeline;
	int			bit_endian;
	int			size;
	int			len;
	int			w_size;
	int			color;
	int			defult_color;
	double		volume;
	double		y_volume;
}	t_image;


typedef struct s_map_data
{
	float			x;
	float			z;
	struct s_map_data	*next;
}	t_map_data;

typedef struct s_vars
{
	t_image *image;
	void	*mlx;
	void	*mlx_win;
	int		ac;
	char 	**av;
	t_map_data **map;
	double		zoom_level;
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
	float start_x;
	float end_x;
	float start_y;
	float end_y;
	int	size;
	int	len;
}	t_data;


typedef struct s_tools
{
	int		fd;
	int		s;
	char	*line;
	char	**split_map;
}	t_tools;

#endif