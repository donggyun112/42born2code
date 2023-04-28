/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:39:27 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/21 22:47:40 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_(char *error)
{
	perror(error);
	exit(0);
}

void	ft_error(char *error)
{
	ft_putstr_fd(error, 2);
	exit(0);
}

void	set_var_2(t_map_data **map, int ac, char **av, t_vars *var)
{
	var->map = map;
	var->ac = ac;
	var->av = av;
}

int	main(int ac, char **av)
{
	t_vars		var;
	t_image		data;
	t_map_data	**map;

	if (ac != 2)
		error_("argument Error");
	if (is_valid_file_type(av[1]) == 0)
		ft_error("file Error\n");
	var.mlx = mlx_init();
	var.mlx_win = mlx_new_window(var.mlx, 1100, 800, "fdf");
	data.image = mlx_new_image(var.mlx, 1100, 800);
	data.addr = mlx_get_data_addr(data.image, &data.bit_pixel, \
	&data.bit_sizeline, &data.bit_endian);
	var.image = &data;
	data.z_rota = 1;
	set_var(&var);
	data.volume = var.zoom_level;
	data.y_volume = 1;
	map = read_map(av, &data, 0);
	put_map_w(map, &data);
	set_var_2(map, ac, av, &var);
	engine(&var);
	mlx_put_image_to_window(var.mlx, var.mlx_win, var.image->image, 0, 0);
	mlx_loop(var.mlx);
	exit(0);
}
